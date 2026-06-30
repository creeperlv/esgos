#include "esgos_engine.h"
#include "esgos_duktape_funcs.h"

static duk_ret_t gfx_print(duk_context *ctx)
{
    M5.Display.printf("%s", duk_to_string(ctx, 0));
    return 0;
}
static duk_ret_t get_version(duk_context *ctx)
{
    duk_push_string(ctx, esgos_version());
    return 1;
}
static void (*to_home_func)();
static esgos_engine_app_stop app_stop_func;
static esgos_launch_app esgos_launch_app_func;
static duk_ret_t duk_to_home(duk_context *ctx)
{
    to_home_func();
    return 0;
}
static duk_ret_t duk_esgos_engine_app_stop(duk_context *ctx)
{
    app_stop_func(ctx);
    return 0;
}
static duk_ret_t duk_esgos_open_app(duk_context *ctx)
{
    const char *main_app_path = duk_to_string(ctx, 0);
    esgos_launch_app_func(main_app_path);
    return 0;
}
static void fatal_handler(void *udata, const char *msg)
{
    esgos_ui_clear_screen();
    esgos_ui_set_font72();
    esgos_ui_set_cursor(0, 0);
    esgos_ui_print("\n  :(\n\n");
    esgos_ui_set_font24();
    esgos_ui_print("Your device ran into a problem and needs to restart\n");
    esgos_ui_print("Please manually restart via the hardware reset button.\n");
    esgos_ui_set_font16();
    show_errln("****Engine Fatal Error****");
    show_errln("FALAL ERROR");
    if (msg)
        show_errln(msg);
    else
        show_errln("no message");
    while (1)
        delay(1000);
}

void *esgos_create_engine_context()
{
    duk_context *
        // ctx = duk_create_heap_default();

        ctx = duk_create_heap(NULL, NULL, NULL, NULL, fatal_handler);
    // duk_push_c_function(ctx, gfx_print, 1);
    // duk_put_global_string(ctx, "print");

    // duk_push_c_function(ctx, duk_esgos_engine_app_stop, 0);
    // duk_put_global_string(ctx, "exit");
    // esgos_dt_bind_all(ctx);
    return ctx;
}

void esgos_destroy_engine_context(void *engine_context)
{
    duk_destroy_heap((duk_context *)engine_context);
}

void esgos_bind_to_home(void (*to_home)())
{
    to_home_func = to_home;
}

void esgos_bind_app_stop(esgos_engine_app_stop func)
{
    app_stop_func = func;
}

void esgos_bind_esgos_launch_app(esgos_launch_app func)
{
    esgos_launch_app_func = func;
}

void esgos_load_script(void *engine_context, const char *script)
{
    duk_peval_string((duk_context *)engine_context, script);
}

void esgos_load_script_no_result(void *engine_context, const char *script)
{
    duk_pcompile_string((duk_context *)engine_context, 0, script);
    duk_call((duk_context *)engine_context, 0);
    // duk_eval_string_noresult((duk_context *)engine_context, script);
}
static bool ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return false; // Handle null pointer safety

    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if (suffix_len > str_len)
        return false;

    return strcmp(str + str_len - suffix_len, suffix) == 0;
}
void esgos_load_script_from_file(void *engine_context, const char *file_path)
{
    if (ends_with(file_path, ".bin"))
    {
        uint8_t *data = nullptr;
        size_t length = 0;
        void *handle = esgos_fs_open(file_path, "rb");
        esgos_fs_read_all_data(handle, &data, &length);
        esgos_fs_close(handle);
        esgos_load_bytecode(engine_context, (void *)data, length);
        duk_call((duk_context *)engine_context, 0);
        free(data);
    }
    else
    {
        char *script = esgos_fs_read_file_path_all_cstr(file_path);
        esgos_load_script_no_result(engine_context, (const char *)script);
        free(script);
    }
}

void esgos_load_script_fn(void *engine_context, char *script, char *fn)
{
    duk_push_string((duk_context *)engine_context, fn);
    duk_compile_string_filename((duk_context *)engine_context, 0, script);
}

duk_ret_t esgos_dt_core_load_library(duk_context *ctx)
{
    const char *fp = duk_to_string(ctx, 0);
    esgos_load_script_from_file((void *)ctx, fp);
    return 0;
}
void esgos_load_bytecode(void *engine_context, void *data, size_t data_size)
{
    uint8_t *buf;
    uint8_t *data_u8 = (uint8_t *)data;
    buf = (uint8_t *)duk_push_fixed_buffer((duk_context *)engine_context, (size_t)data_size);
    for (size_t i = 0; i < data_size; i++)
    {
        buf[i] = data_u8[i];
    }
    duk_load_function((duk_context *)engine_context);
}

void esgos_call_func_with_return(void *engine_context, char *func)
{
    duk_eval_string((duk_context *)engine_context, func);
}

void esgos_engine_setup_system_app_api(void *engine_context)
{
    duk_context *ctx = (duk_context *)engine_context;
    duk_push_c_function(ctx, duk_to_home, 0);
    duk_put_global_string(ctx, "to_home");
}

void esgos_call_func(void *engine_context, const char *func)
{
    duk_eval_string_noresult((duk_context *)engine_context, func);
}

void esgos_call_handle_file(void *engine_context, char *file_path)
{
    duk_context *ctx = (duk_context *)engine_context;
    duk_get_global_string(ctx, "HandleFile");
    duk_push_string(ctx, file_path);
    duk_call(ctx, 1);
}

void esgos_call_init(void *engine_context)
{
    duk_eval_string_noresult((duk_context *)engine_context, "init();");
}

void esgos_call_loop(void *engine_context)
{
    duk_eval_string_noresult((duk_context *)engine_context, "loop();");
}
