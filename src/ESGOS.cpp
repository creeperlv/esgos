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
void *current_app;
void *home_app;
void *file_manager_app;
void *settings_app;
static bool is_show_boot_log;

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
    current_app = home_app;
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
#define APP_PATH_HOME "/system/home/app.js"
#define APP_PATH_HOME_DIR "/system/home/"
#define APP_PATH_FM "/system/explorer/app.js"
#define APP_PATH_FM_DIR "/system/explorer/"
#define APP_PATH_SETTINGS "/system/settings/app.js"
#define APP_PATH_SETTINGS_DIR "/system/settings/"
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
    home_app = esgos_create_engine_context();
    show_logln("Engine: Home App context inited.");
    esgos_engine_setup_system_app_api(home_app);
    esgos_dt_bind_all((duk_context *)home_app);
    esgos_dt_bind_system((duk_context *)home_app);
    show_logln("Engine: Home App calls inited.");
    {
        if (!esgos_fs_is_exists(APP_PATH_HOME))
        {
            show_warnln("Home App not found!");
            show_warnln("Loading embedded version instead!");
            load_embedded_home();
            goto SKIP_HOME;
        }
        if (esgos_fs_is_directory(APP_PATH_HOME))
        {
            show_warnln("Home App corrupted!");
            show_warnln("Loading embedded version instead!");
            load_embedded_home();
            goto SKIP_HOME;
        }
        esgos_app_host_load_deps_with_depfn(home_app,APP_PATH_HOME_DIR,APP_PATH_HOME_DIR esgos_dep_file_name);
        load_script(home_app, APP_PATH_HOME);
    SKIP_HOME:;
        esgos_call_init(home_app);
    }
    show_logln("Engine: Home App loaded.");

    file_manager_app = esgos_create_engine_context();
    show_logln("Engine: File Manager App context inited.");
    {
        if (!esgos_fs_is_exists(APP_PATH_FM))
        {
            show_warnln("File Manager App not found!");
            show_warnln("Loading embedded version instead!");
            load_embedded_fm();
            goto SKIP_FM;
        }
        if (esgos_fs_is_directory(APP_PATH_FM))
        {
            show_warnln("File Manager App corrupted!");
            show_warnln("Loading embedded version instead!");
            load_embedded_fm();
            goto SKIP_FM;
        }
        load_script(file_manager_app, APP_PATH_FM);
        
    SKIP_FM:;
        esgos_call_init(file_manager_app);
    }
    show_logln("Engine: File Manager App loaded.");

    settings_app = esgos_create_engine_context();
    show_logln("Engine: Settings App loaded.");
    {
        if (!esgos_fs_is_exists(APP_PATH_SETTINGS))
        {
            show_errln("Settings App not found!");
            show_warnln("Loading embedded version instead!");
            load_embedded_settings();
            goto SKIP_SETTINGS;
        }
        if (esgos_fs_is_directory(APP_PATH_SETTINGS))
        {
            show_errln("Settings App corrupted!");
            show_warnln("Loading embedded version instead!");
            load_embedded_settings();
            goto SKIP_SETTINGS;
        }
        load_script(settings_app, APP_PATH_SETTINGS);
    SKIP_SETTINGS:;
        esgos_call_init(settings_app);
    }
    show_logln("Engine: Settings App context inited.");
    esgos_bind_to_home(to_home);
    to_home();
    delay(1000);
}
bool esgos_check_status_bar()
{
    if (info.is_app_switched)
    {
        info.is_app_switched = false;
        return true;
    }
    return false;
}
void esgos_draw_status_bar()
{
    if (esgos_check_status_bar() == false)
        return;
    esgos_ui_fill_rectangle(0, 0, esgos_ui_get_screen_w(), info.status_bar_height, esgos_ui_get_color_white());
    {

        int32_t bat = M5.Power.getBatteryLevel();

        int BatIconW = 30;
        float v = bat / 100.0f;
        {
            auto BLACK = esgos_ui_get_color_black();
            auto WHITE = esgos_ui_get_color_white();
            esgos_ui_fill_rectangle(esgos_ui_get_screen_w() - 5 - BatIconW, 4, BatIconW, 12, BLACK);
            esgos_ui_fill_rectangle(esgos_ui_get_screen_w() - 5 - BatIconW + 1, 5, BatIconW - 2, 10, WHITE);
            esgos_ui_fill_rectangle(esgos_ui_get_screen_w() - 5 - BatIconW + 2, 6, (BatIconW - 4) * v, 8, BLACK);
        }
    }
}
m5::touch_detail_t touchDetail;
void loop()
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
        esgos_call_loop(current_app);
        esgos_draw_status_bar();
    }
    delay(10);
}
