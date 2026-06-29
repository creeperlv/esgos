#ifndef __ESGOS_UI_H__
#define __ESGOS_UI_H__
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <M5Unified.h>
#include <M5GFX.h>
#include "esgos_core.h"
typedef enum esgos_ui_global_state
{
    esgos_ui_global_state_default,
    esgos_ui_global_state_input,
} esgos_ui_global_state;
typedef struct esgos_ui_core_info
{
    bool is_pressed;
    bool is_app_switched;
    bool full_refresh_requested;
    int touch_x;
    int touch_y;
    int status_bar_height;
    esgos_ui_global_state global_state;
} esgos_ui_core_info;
void esgos_ui_init(esgos_ui_core_info *info);
esgos_ui_core_info * esgos_ui_get_info();
char *esgos_ui_get_global_input();
void esgos_ui_draw_input();
void esgos_ui_set_cursor(int x, int y);
int esgos_ui_get_screen_w();
int esgos_ui_get_screen_h();
void esgos_ui_clear_screen();
void esgos_ui_print(const char *str);
void esgos_ui_printf(const char *format, ...);
void esgos_ui_println(const char *str);
void esgos_ui_fill_rectangle(int x, int y, int w, int h,void* color);
void esgos_ui_set_text_color(void* color);
void esgos_ui_draw_box(int x, int y, int w, int h,void* color);
void esgos_ui_draw_string_center(const char *str, int x, int y);
void esgos_ui_draw_string_center_font(const char *str, int x, int y, void *font);
void esgos_ui_draw_string(const char *str, int x, int y);
void esgos_ui_draw_string_font(const char *str, int x, int y, void *font);
void esgos_ui_draw_png_data(uint8_t *data, int x, int y, int w, int h, float scaleX, float scaleY);
void esgos_ui_draw_png_file(const char *str, int x, int y, int w, int h, float scaleX, float scaleY);
void esgos_ui_draw_png_data_center(uint8_t *data, int x, int y, int w, int h, float scaleX, float scaleY);
void esgos_ui_draw_png_file_center(const char *str, int x, int y, int w, int h, float scaleX, float scaleY);
void *esgos_ui_get_font16();
void *esgos_ui_get_font18();
void *esgos_ui_get_font24();
void *esgos_ui_get_font36();
void *esgos_ui_get_font40();
void *esgos_ui_get_font72();
void esgos_ui_set_font(void *font);
void esgos_ui_set_font16();
void esgos_ui_set_font18();
void esgos_ui_set_font24();
void esgos_ui_set_font36();
void esgos_ui_set_font40();
void esgos_ui_set_font72();
void *esgos_ui_get_color_white();
void *esgos_ui_get_color_black();
#endif