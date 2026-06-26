#include "esgos_duktape_funcs.h"

static duk_function_list_entry ui_funcs[] = {
    {"DrawCenterString", esgos_dt_ui_draw_center_string, 3},
    {"DrawCenterStringFont", esgos_dt_ui_draw_center_string_font, 4},
    {"GetScreenW", esgos_dt_ui_get_screen_w, 0},
    {"GetScreenH", esgos_dt_ui_get_screen_h, 0},
    {"GetStatusBarHeight", esgos_dt_ui_get_status_bar_height, 0},
    {"GetFont16", esgos_dt_ui_get_font16, 0},
    {"GetFont24", esgos_dt_ui_get_font24, 0},
    {"GetFont40", esgos_dt_ui_get_font40, 0},
    {"ClearScreen", esgos_dt_ui_full_screen_clear, 0},
    {"FillRect", esgos_dt_ui_fill_rect, 5},
    {"DrawBox", esgos_dt_ui_draw_box, 5},
    {"GetWhite", esgos_dt_ui_get_white, 0},
    {"GetBlack", esgos_dt_ui_get_black, 0},
    {"SetTextColor", esgos_dt_ui_set_text_color, 1},
    {"SetTextCursor", esgos_dt_ui_set_text_cursor, 2},
    {"SetTextFont", esgos_dt_ui_set_text_font, 1},
    {"DrawPngFile", esgos_dt_ui_draw_image_png_file, 7},
    {NULL, NULL, 0}};

static duk_function_list_entry core_funcs[] = {
    {"Log", esgos_dt_core_log, 1},
    {"Delay", esgos_dt_core_delay, 1},
    {"Write", esgos_dt_core_write, 1},
    {"WriteLine", esgos_dt_core_write_line, 1},
    {"LaunchApp", esgos_dt_core_launch_app, 1},
    {"GetVersion", esgos_dt_core_get_version, 0},
    {"GetRelease", esgos_dt_core_get_release, 0},
    {NULL, NULL, 0}};

static duk_function_list_entry touch_funcs[] = {
    {"IsPress", esgos_dt_touch_is_press, 0},
    {"PosX", esgos_dt_touch_position_x, 0},
    {"PosY", esgos_dt_touch_position_y, 0},
    {NULL, NULL, 0}};

static duk_function_list_entry fs_funcs[] = {
    {"Exists", esgos_dt_fs_exists, 1},
    {"Open", esgos_dt_fs_open, 2},
    {"Close", esgos_dt_fs_close, 1},
    {NULL, NULL, 0}};

duk_ret_t esgos_dt_core_log(duk_context *ctx)
{
    show_logln(duk_get_string(ctx, 0));
    return 0;
}

duk_ret_t esgos_dt_core_delay(duk_context *ctx)
{
    delay((uint32_t)duk_get_number(ctx, 0));
    return 0;
}

duk_ret_t esgos_dt_core_write(duk_context *ctx)
{
    esgos_ui_print(duk_to_string(ctx, 0));
    return 0;
}
duk_ret_t esgos_dt_core_write_line(duk_context *ctx)
{
    esgos_ui_println(duk_to_string(ctx, 0));
    return 0;
}
duk_ret_t esgos_dt_core_get_version(duk_context *ctx)
{
    duk_push_string(ctx, esgos_version());
    return 1;
}
duk_ret_t esgos_dt_core_get_release(duk_context *ctx)
{
    duk_push_string(ctx, esgos_release_channel());
    return 1;
}
void esgos_dt_bind_ui(duk_context *ctx)
{
    // duk_push_c_function(ctx, esgos_dt_ui_draw_center_string, 3);
    // duk_push_string(ctx, "DrawCenterString");
    // duk_push_c_function(ctx, esgos_dt_ui_draw_center_string_font, 4);
    // duk_push_string(ctx, "DrawCenterStringWFont");

    duk_push_global_object(ctx);
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, ui_funcs);
    duk_put_prop_string(ctx, -2, "UI");
    duk_pop(ctx);
}

void esgos_dt_bind_touch(duk_context *ctx)
{
    duk_push_global_object(ctx);
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, touch_funcs);
    duk_put_prop_string(ctx, -2, "Touch");
    duk_pop(ctx);
}

void esgos_dt_bind_core(duk_context *ctx)
{
    duk_push_global_object(ctx);
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, core_funcs);
    duk_put_prop_string(ctx, -2, "Core");
    duk_pop(ctx);
}

void esgos_dt_bind_fs(duk_context *ctx)
{
    duk_push_global_object(ctx);
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, fs_funcs);
    duk_put_prop_string(ctx, -2, "FS");
    duk_pop(ctx);
}

void esgos_dt_bind_all(duk_context *ctx)
{
    esgos_dt_bind_fs(ctx);
    esgos_dt_bind_touch(ctx);
    esgos_dt_bind_core(ctx);
    esgos_dt_bind_ui(ctx);
}

duk_ret_t esgos_dt_ui_draw_box(duk_context *ctx)
{
    void *color = duk_get_pointer(ctx, 4);
    int x = (int)duk_get_number(ctx, 0);
    int y = (int)duk_get_number(ctx, 1);
    int w = (int)duk_get_number(ctx, 2);
    int h = (int)duk_get_number(ctx, 3);
    esgos_ui_draw_box(x, y, w, h, color);
    return 0;
}

duk_ret_t esgos_dt_ui_draw_center_string(duk_context *ctx)
{
    int y = (int)duk_get_number(ctx, 2);
    int x = (int)duk_get_number(ctx, 1);
    const char *content = duk_get_string(ctx, 0);
    esgos_ui_draw_string_center(content, x, y);
    return 0;
}

duk_ret_t esgos_dt_ui_draw_center_string_font(duk_context *ctx)
{
    void *font = duk_get_pointer(ctx, 3);
    int y = (int)duk_get_number(ctx, 2);
    int x = (int)duk_get_number(ctx, 1);
    const char *content = duk_get_string(ctx, 0);
    esgos_ui_draw_string_center_font(content, x, y, font);
    return 0;
}

duk_ret_t esgos_dt_ui_fill_rect(duk_context *ctx)
{
    void *color = duk_get_pointer(ctx, 4);
    int x = (int)duk_get_number(ctx, 0);
    int y = (int)duk_get_number(ctx, 1);
    int w = (int)duk_get_number(ctx, 2);
    int h = (int)duk_get_number(ctx, 3);
    esgos_ui_fill_rectangle(x, y, w, h, color);
    return 0;
}

duk_ret_t esgos_dt_ui_full_screen_clear(duk_context *ctx)
{
    esgos_ui_clear_screen();
    return 0;
}

duk_ret_t esgos_dt_ui_set_text_color(duk_context *ctx)
{
    void *color = duk_get_pointer(ctx, 0);
    esgos_ui_set_text_color(color);
    return 0;
}

duk_ret_t esgos_dt_ui_set_text_cursor(duk_context *ctx)
{
    int y = (int)duk_get_number(ctx, 1);
    int x = (int)duk_get_number(ctx, 0);
    esgos_ui_set_cursor(x, y);
    return 0;
}

duk_ret_t esgos_dt_ui_set_text_font(duk_context *ctx)
{
    void* font_ptr=duk_get_pointer(ctx, 0);
    esgos_ui_set_font(font_ptr);
    return 0;
}

duk_ret_t esgos_dt_fs_open(duk_context *ctx)
{
    const char *file = duk_get_string(ctx, 0);
    const char *mode = duk_get_string(ctx, 1);
    void *fp = esgos_fs_open(file, mode);
    duk_push_pointer(ctx, fp);
    return 1;
}

duk_ret_t esgos_dt_fs_exists(duk_context *ctx)
{
    duk_push_boolean(ctx, esgos_fs_is_exists(duk_get_string(ctx, 0)));
    return 1;
}

duk_ret_t esgos_dt_fs_close(duk_context *ctx)
{
    void *fp = duk_get_pointer(ctx, 0);
    esgos_fs_close(fp);
    return 0;
}

duk_ret_t esgos_dt_ui_draw_image_png_file(duk_context *ctx)
{

    const char *content = duk_get_string(ctx, 0);
    int x = (int32_t)duk_get_number(ctx, 1);
    int y = (int32_t)duk_get_number(ctx, 2);
    int w = (int32_t)duk_get_number(ctx, 3);
    int h = (int32_t)duk_get_number(ctx, 4);
    double sx = duk_get_number(ctx, 5);
    double sy = duk_get_number(ctx, 6);
    esgos_ui_draw_png_file(content, x, y, w, h, sx, sy);
    return 0;
}

duk_ret_t esgos_dt_ui_get_screen_w(duk_context *ctx)
{
    duk_push_number(ctx, (double)esgos_ui_get_screen_w());
    return 1;
}

duk_ret_t esgos_dt_ui_get_screen_h(duk_context *ctx)
{
    duk_push_number(ctx, (double)esgos_ui_get_screen_h());
    return 1;
}

duk_ret_t esgos_dt_ui_get_font16(duk_context *ctx)
{
    duk_push_pointer(ctx, esgos_ui_get_font16());
    return 1;
}

duk_ret_t esgos_dt_ui_get_font24(duk_context *ctx)
{
    duk_push_pointer(ctx, esgos_ui_get_font24());
    return 1;
}

duk_ret_t esgos_dt_ui_get_font40(duk_context *ctx)
{
    duk_push_pointer(ctx, esgos_ui_get_font40());
    return 1;
}

duk_ret_t esgos_dt_ui_get_white(duk_context *ctx)
{
    duk_push_pointer(ctx, esgos_ui_get_color_white());
    return 1;
}

duk_ret_t esgos_dt_ui_get_black(duk_context *ctx)
{
    duk_push_pointer(ctx, esgos_ui_get_color_black());
    return 1;
}

duk_ret_t esgos_dt_ui_get_status_bar_height(duk_context *ctx)
{
    duk_push_number(ctx, (double)esgos_ui_get_info()->status_bar_height);
    return 1;
}

duk_ret_t esgos_dt_touch_is_press(duk_context *ctx)
{
    duk_push_boolean(ctx, esgos_ui_get_info()->is_pressed ? true : false);
    return 1;
}

duk_ret_t esgos_dt_touch_position_x(duk_context *ctx)
{
    duk_push_number(ctx, (double)esgos_ui_get_info()->touch_x);
    return 1;
}

duk_ret_t esgos_dt_touch_position_y(duk_context *ctx)
{
    duk_push_number(ctx, (double)esgos_ui_get_info()->touch_y);
    return 1;
}
