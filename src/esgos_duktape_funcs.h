#ifndef __ESGOS_DUKTAP_FUNCS__
#define __ESGOS_DUKTAP_FUNCS__
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <M5Unified.h>
#include <M5GFX.h>
#include "esgos_fs.h"
#include "esgos_ui.h"
#include "esgos_core.h"
#include "duktape.h"

duk_ret_t esgos_dt_ui_draw_box(duk_context *ctx);

duk_ret_t esgos_dt_ui_draw_string(duk_context *ctx);
duk_ret_t esgos_dt_ui_draw_string_font(duk_context *ctx);
duk_ret_t esgos_dt_ui_draw_center_string(duk_context *ctx);
duk_ret_t esgos_dt_ui_draw_center_string_font(duk_context *ctx);

duk_ret_t esgos_dt_ui_fill_rect(duk_context *ctx);

duk_ret_t esgos_dt_ui_set_text_color(duk_context *ctx);
duk_ret_t esgos_dt_ui_set_text_cursor(duk_context *ctx);
duk_ret_t esgos_dt_ui_set_text_scroll(duk_context *ctx);
duk_ret_t esgos_dt_ui_set_text_font(duk_context *ctx);

duk_ret_t esgos_dt_ui_draw_image_png(duk_context *ctx);
duk_ret_t esgos_dt_ui_draw_image_png_file(duk_context *ctx);
duk_ret_t esgos_dt_ui_draw_image_png_file_center(duk_context *ctx);

duk_ret_t esgos_dt_ui_get_screen_w(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_screen_h(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_font16(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_font18(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_font24(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_font40(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_white(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_black(duk_context *ctx);
duk_ret_t esgos_dt_ui_get_status_bar_height(duk_context *ctx);

duk_ret_t esgos_dt_touch_is_press(duk_context *ctx);
duk_ret_t esgos_dt_touch_position_x(duk_context *ctx);
duk_ret_t esgos_dt_touch_position_y(duk_context *ctx);

duk_ret_t esgos_dt_fs_open(duk_context *ctx);
duk_ret_t esgos_dt_fs_exists(duk_context *ctx);
duk_ret_t esgos_dt_fs_is_directory(duk_context *ctx);
duk_ret_t esgos_dt_fs_open_next_dir(duk_context *ctx);
duk_ret_t esgos_dt_fs_close(duk_context *ctx);
duk_ret_t esgos_dt_fs_read_all_string(duk_context *ctx);
duk_ret_t esgos_dt_fs_seek(duk_context *ctx);
duk_ret_t esgos_dt_fs_position(duk_context *ctx);
duk_ret_t esgos_dt_fs_read(duk_context *ctx);
duk_ret_t esgos_dt_fs_read_char(duk_context *ctx);

duk_ret_t esgos_dt_core_load_library(duk_context *ctx);
duk_ret_t esgos_dt_core_log(duk_context *ctx);
duk_ret_t esgos_dt_core_delay(duk_context *ctx);
duk_ret_t esgos_dt_core_write(duk_context *ctx);
duk_ret_t esgos_dt_core_write_line(duk_context *ctx);

void esgos_dt_bind_ui(duk_context *ctx);
void esgos_dt_bind_touch(duk_context *ctx);
void esgos_dt_bind_core(duk_context *ctx);
void esgos_dt_bind_fs(duk_context *ctx);

void esgos_dt_bind_all(duk_context *ctx);
#endif