#include "esgos_app_host.h"
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <string>

void esgos_app_host_load_deps(void *engine_context, const char *app_dir)
{
    std::string full_path = std::string(app_dir) + "/esgos.dep";
    const char *full_dep_file = full_path.c_str();
    esgos_app_host_load_deps_with_depfn(engine_context, app_dir, full_dep_file);
}

void esgos_app_host_load_deps_with_depfn(void *engine_context, const char *app_dir, const char *dep_file)
{
    auto fp = esgos_fs_open(dep_file, "r");
    while (1)
    {
        char *entry = esgos_fs_read_line(fp);
        if (entry == nullptr)
        {
            break;
        }
        show_logln(entry);
        // delay(1000);
        esgos_load_script_from_file(engine_context, entry);
        free(entry);
    }
    esgos_fs_close(fp);
}

void *esgos_app_host_start_app(const char *app_dir)
{
    void *ptr = esgos_create_engine_context();

    // esgos_dt_bind_all((duk_context *)ptr);

    esgos_app_host_load_deps(ptr, app_dir);
    std::string full_path = std::string(app_dir) + "/app.js";
    std::string full_path_bin = std::string(app_dir) + "/app.bin";
    const char *app_js_path = full_path.c_str();
    const char *app_bin_path = full_path_bin.c_str();
    if (esgos_fs_is_exists(app_bin_path))
    {
        esgos_load_script_from_file(ptr, app_bin_path);
    }
    else
    {

        char *script = esgos_fs_read_file_path_all_cstr(app_js_path);
        esgos_load_script_no_result(ptr, script);
        free(script);
    }
    return ptr;
}

void *esgos_app_host_start_system_app(const char *app_dir)
{
    void *ptr = esgos_create_engine_context();

    // esgos_engine_setup_system_app_api(ptr);
    esgos_dt_bind_all((duk_context *)ptr);
    esgos_dt_bind_system((duk_context *)ptr);
    esgos_app_host_load_deps(ptr, app_dir);
    std::string full_path = std::string(app_dir) + "/app.js";
    std::string full_path_bin = std::string(app_dir) + "/app.bin";
    const char *app_js_path = full_path.c_str();
    const char *app_bin_path = full_path_bin.c_str();
    if (esgos_fs_is_exists(app_bin_path))
    {
        esgos_load_script_from_file(ptr, app_bin_path);
    }
    else
    {

        char *script = esgos_fs_read_file_path_all_cstr(app_js_path);
        esgos_load_script_no_result(ptr, script);
        free(script);
    }
    return ptr;
}

duk_ret_t esgos_dt_core_launch_app(duk_context *ctx)
{
    const char *app_folder = duk_to_string(ctx, 0);
    esgos_core_schedule_launch_app(app_folder, false);
    return 0;
}

duk_ret_t esgos_dt_system_launch_sys_app(duk_context *ctx)
{
    const char *app_folder = duk_to_string(ctx, 0);
    esgos_core_schedule_launch_app(app_folder, true);
    return 0;
}