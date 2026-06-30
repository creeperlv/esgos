#include "esgos_ui.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <M5Unified.h>
#include <M5GFX.h>
static esgos_ui_core_info *ui_core_info;
static int ESGOS_COLOR_WHITE = TFT_WHITE;
static int ESGOS_COLOR_BLACK = TFT_BLACK;
void esgos_ui_init(esgos_ui_core_info *info)
{
    ui_core_info = info;
    info->global_state = esgos_ui_global_state_default;
    info->status_bar_height = 20;
    info->is_app_switched = true;
}

esgos_ui_core_info *esgos_ui_get_info()
{
    return ui_core_info;
}

void esgos_ui_draw_input()
{
}

void esgos_ui_set_cursor(int x, int y)
{
    M5.Display.setCursor(x, y);
}
int esgos_ui_get_screen_w()
{
    return M5.Display.width();
}
int esgos_ui_get_screen_h()
{
    return M5.Display.height();
}
void esgos_ui_clear_screen()
{
    int w = esgos_ui_get_screen_w();
    int h = esgos_ui_get_screen_h();
    esgos_ui_fill_rectangle(0, 0, w, h, esgos_ui_get_color_white());
    ui_core_info->full_refresh_requested = true;
}
void esgos_ui_print(const char *str)
{
    M5.Display.print(str);
}
void esgos_ui_printf(const char *format, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    M5.Display.print(buffer);
}
void esgos_ui_println(const char *str)
{
    M5.Display.println(str);
}
void esgos_ui_fill_rectangle(int x, int y, int w, int h, void *color)
{
    M5.Display.fillRect(x, y, w, h, ((int *)color)[0]);
}
void esgos_ui_set_text_color(void *color)
{
    M5.Display.setTextColor(((int *)color)[0]);
}
void esgos_ui_draw_box(int x, int y, int w, int h, void *color)
{
    int c = ((int *)color)[0];
    M5.Display.drawFastHLine(x, y, w, c);
    M5.Display.drawFastHLine(x, y + h, w, c);
    M5.Display.drawFastVLine(x, y, h, c);
    M5.Display.drawFastVLine(x + w, y, h, c);
}
void esgos_ui_draw_string_center(const char *str, int x, int y)
{
    M5.Display.drawCenterString(str, x, y);
}
void esgos_ui_draw_string_center_font(const char *str, int x, int y, void *font)
{
    M5.Display.drawCenterString(str, x, y, (lgfx::v1::IFont *)font);
}
void esgos_ui_draw_string(const char *str, int x, int y)
{
    M5.Display.drawString(str, x, y);
}
void *esgos_ui_get_color_white()
{
    return &ESGOS_COLOR_WHITE;
}

void *esgos_ui_get_color_black()
{
    return &ESGOS_COLOR_BLACK;
}

void esgos_ui_draw_png_file(const char *str, int x, int y, int w, int h, float scaleX, float scaleY)
{
    M5.Display.drawPngFile(SD, str, x, y, w, h, 0, 0, scaleX, scaleY, datum_t::top_left);
}

void esgos_ui_draw_png_file_center(const char *str, int x, int y, int w, int h, float scaleX, float scaleY)
{
    M5.Display.drawPngFile(SD, str, x, y, w, h, 0, 0, scaleX, scaleY, datum_t::middle_center);
}

void *esgos_ui_get_font16()
{
    return (void *)&fonts::efontCN_16;
}

void *esgos_ui_get_font18()
{
    return (void *)&fonts::DejaVu18;
}

void *esgos_ui_get_font24()
{
    return (void *)&fonts::efontCN_24;
}

void *esgos_ui_get_font36()
{
    return (void *)&fonts::lgfxJapanGothic_36;
}

void *esgos_ui_get_font40()
{
    return (void *)&fonts::DejaVu40;
}

void *esgos_ui_get_font72()
{
    return (void *)&fonts::DejaVu72;
}

void esgos_ui_set_font(void *font)
{
    M5.Display.setFont(static_cast<lgfx::IFont *>(font));
}

void esgos_ui_set_font16()
{
    M5.Display.setFont(&fonts::efontCN_16);
}

void esgos_ui_set_font18()
{
    M5.Display.setFont(static_cast<lgfx::IFont *>(esgos_ui_get_font18()));
}

void esgos_ui_set_font24()
{
    M5.Display.setFont(static_cast<lgfx::IFont *>(esgos_ui_get_font24()));
}

void esgos_ui_set_font36()
{
    M5.Display.setFont(static_cast<lgfx::IFont *>(esgos_ui_get_font36()));
}

void esgos_ui_set_font40()
{
    M5.Display.setFont(static_cast<lgfx::IFont *>(esgos_ui_get_font40()));
}

void esgos_ui_set_font72()
{
    M5.Display.setFont(static_cast<lgfx::IFont *>(esgos_ui_get_font72()));
}

void esgos_ui_set_epd_mode(int mode)
{
    M5.Display.setEpdMode((epd_mode_t)mode);
}
