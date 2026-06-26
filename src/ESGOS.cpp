#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <Update.h>
#include <WiFi.h>
#include <M5Unified.h>
#include <M5GFX.h>
#include <USB.h>
#include <USBMSC.h>
#include "duktape.h"
#include "esgos_core.h"
#include "esgos_ui.h"
#include "esgos_fs.h"
#include "esgos_engine.h"
#include "esgos_system_apps.h"
#include "esgos_app_host.h"
#include "esgos_system_funcs.h"

#define APP_PATH_HOME "/system/home/app.js"
#define APP_PATH_HOME_DIR "/system/home/"
#define APP_PATH_FM "/system/explorer/app.js"
#define APP_PATH_FM_DIR "/system/explorer/"
#define APP_PATH_SETTINGS "/system/settings/app.js"
#define APP_PATH_SETTINGS_DIR "/system/settings/"

void *current_app;
void *home_app;
void *file_manager_app;
void *settings_app;
static bool is_show_boot_log;
static const char *app_to_launch = nullptr;
static bool app_is_sys_app = false;
m5::touch_detail_t touchDetail;
static void show_log(const char *str)
{
    if (is_show_boot_log)
        esgos_ui_printf("[%f]%s", millis() / 1000.0, str);
}
static void show_log_unformated(const char *str)
{
    if (is_show_boot_log)
        esgos_ui_print(str);
}
void show_logln(const char *str)
{
    if (is_show_boot_log)
        esgos_ui_printf("[%f]%s\n", millis() / 1000.0, str);
}
static void show_errln(const char *str)
{
    esgos_ui_printf("[%f][Error]%s\n", millis() / 1000.0, str);
}

static void show_warnln(const char *str)
{
    esgos_ui_printf("[%f][Warning]%s\n", millis() / 1000.0, str);
}
static bool system_app_switched = false;
static void to_home()
{
    system_app_switched = true;
    // current_app = home_app;
    app_to_launch = APP_PATH_HOME_DIR;
}
static void esgos_halt()
{
    while (1)
        delay(1000);
}
static void init_fs()
{
    if (!esgos_fs_init())
    {
        show_errln("[FAIL]SD card not detected.");
        esgos_halt();
    }
}
static void load_script(void *context, const char *path)
{
    char *script = esgos_fs_read_file_path_all_cstr(path);
    M5.Display.printf("%d", strlen(script));
    delay(1000);
    esgos_load_script_no_result(context, script);
    free(script);
}
void draw_logo()
{
    if (esgos_fs_is_exists("/boot/logo.png"))
    {
        show_logln("Boot logo found.");
        esgos_ui_draw_png_file_center("/boot/logo.png", 0, 0, 0, 0, 1, 1);
    }
    else
    {
        esgos_ui_draw_string_center_font("esGOS", esgos_ui_get_screen_w() / 2, esgos_ui_get_screen_h() / 2 - 20, esgos_ui_get_font40());
        show_logln("Boot logo not found.");
    }
}
esgos_ui_core_info info;
static void load_embedded_home()
{
    esgos_load_script(home_app, esgos_system_embedded_home);
}
static void load_embedded_fm()
{
    esgos_load_script(file_manager_app, esgos_system_embedded_home);
}
static void load_embedded_settings()
{
    esgos_load_script(settings_app, esgos_system_embedded_home);
}
static void to_settings()
{
    system_app_switched = true;
    current_app = settings_app;
}

void esgos_core_schedule_launch_app(const char *app, bool is_system_app)
{
    app_to_launch = app;
    app_is_sys_app = is_system_app;
}
int32_t bat = -1;
int32_t _bat = -1;
bool esgos_check_status_bar()
{
    bat = M5.Power.getBatteryLevel();
    if (info.is_app_switched)
    {
        info.is_app_switched = false;
        return true;
    }
    if (info.full_refresh_requested == true)
        return true;
    if (bat != _bat)
    {
        _bat = bat;
        return true;
    }
    return false;
}
void esgos_draw_status_bar()
{
    if (esgos_check_status_bar() == false)
        return;
    M5.Display.setFont(&fonts::efontCN_16);
    int BatIconW = 30;
    esgos_ui_fill_rectangle(0, 0, esgos_ui_get_screen_w(), info.status_bar_height, esgos_ui_get_color_white());
    M5.Display.setCursor(esgos_ui_get_screen_w() - 50 - BatIconW, 2);
    M5.Display.printf("%d %%", bat);
    {

        float v = bat / 100.0f;
        {
            auto BLACK = esgos_ui_get_color_black();
            auto WHITE = esgos_ui_get_color_white();
            esgos_ui_fill_rectangle(esgos_ui_get_screen_w() - 5 - BatIconW, 4, BatIconW, 12, BLACK);
            esgos_ui_fill_rectangle(esgos_ui_get_screen_w() - 5 - BatIconW + 1, 5, BatIconW - 2, 10, WHITE);
            esgos_ui_fill_rectangle(esgos_ui_get_screen_w() - 5 - BatIconW + 2, 6, (BatIconW - 4) * v, 8, BLACK);
        }
    }
    M5.Display.setCursor(0, 0);
}
static void new_loop()
{

    M5.update();
    touchDetail = M5.Touch.getDetail();
    info.is_pressed = touchDetail.isPressed();
    info.touch_x = touchDetail.x;
    info.touch_y = touchDetail.y;
    if (current_app != esgos_obtain_null())
    {
        if (system_app_switched)
        {
            esgos_call_func(current_app, "wakeup();");
            system_app_switched = false;
        }
        info.full_refresh_requested = false;
        esgos_call_loop(current_app);
        esgos_draw_status_bar();
        {
            if (app_to_launch != nullptr)
            {
                if (current_app != nullptr)
                {
                    esgos_destroy_engine_context(current_app);
                }
                info.is_app_switched = true;
                std::string full_path = std::string(app_to_launch);
                const char *app_dir = full_path.c_str();
                esgos_ui_set_cursor(0, 0);
                if (app_is_sys_app)
                {
                    current_app = esgos_app_host_start_system_app(app_dir);
                    system_app_switched = true;
                }
                else
                {
                    current_app = esgos_app_host_start_app(app_dir);
                }
                esgos_call_init(current_app);
                app_to_launch = nullptr;
                app_is_sys_app = false;
            }
        }
    }
    delay(10);
}
static void esgos_new_main(void *p)
{

    if (app_to_launch != nullptr)
    {
        void *ptr;
        if (app_is_sys_app)
        {
            ptr = esgos_app_host_start_system_app(app_to_launch);
            system_app_switched = true;
        }
        else
        {
            ptr = esgos_app_host_start_app(app_to_launch);
        }
        esgos_call_init(ptr);
        show_logln("Inited.");
        app_to_launch = nullptr;
        app_is_sys_app = false;
        current_app = ptr;
        while (1)
        {
            new_loop();
        }
    }
}
void setup()
{
    M5.begin();
    M5.Display.setRotation(0);
    M5.Display.setTextColor(TFT_BLACK);
    M5.Display.setTextScroll(true);
    esgos_ui_set_cursor(0, 0);
    esgos_ui_set_font16();
    init_fs();
    is_show_boot_log = esgos_is_show_boot_log();

    {
        current_app = esgos_obtain_null();
    }
    draw_logo();
    delay(500);
    {
        esgos_ui_init(&info);
        show_logln("UI: Core Inited.");
    }
    app_to_launch = APP_PATH_HOME_DIR;
    app_is_sys_app = true;
    esgos_bind_to_home(to_home);
    esgos_dt_set_to_settings(to_settings);
    xTaskCreateUniversal(esgos_new_main, "new_main", 128 * 1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
    // to_home();
    vTaskDelete(NULL);
}
void loop()
{
    delay(10000);
}