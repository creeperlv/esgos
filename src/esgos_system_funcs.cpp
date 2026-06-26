#include "esgos_system_funcs.h"

static duk_function_list_entry sys_funcs[] = {
    {"PowerOff", esgos_dt_system_poweroff, 0},
    {"Restart", esgos_dt_system_restart, 0},
    {"StartRomUpdate", esgos_dt_system_rom_update, 0},
    {"FirmwareUpdate", esgos_dt_system_firmware_update, 0},
    {"ToSettings", esgos_dt_system_to_settings, 0},
    {"LaunchSysApp", esgos_dt_system_launch_sys_app, 1},
    {"StartMSC", esgos_dt_system_enable_msc, 0},
    {"StopMSC", esgos_dt_system_disable_msc, 0},
    {"IsMSCStarted", esgos_dt_system_check_msc, 0},
    {NULL, NULL, 0}};
duk_ret_t esgos_dt_system_restart(duk_context *ctx)
{
    esgos_restart();
    return 0;
}
duk_ret_t esgos_dt_system_poweroff(duk_context *ctx)
{
    esgos_poweroff();
    return 0;
}
duk_ret_t esgos_dt_system_firmware_update(duk_context *ctx)
{
    esgos_core_update_default();
    return 0;
}
duk_ret_t esgos_dt_system_rom_update(duk_context *ctx)
{
    return 0;
}
duk_ret_t esgos_dt_system_enable_msc(duk_context *ctx)
{
    esgos_system_usb_msc_start();
    return 0;
}
duk_ret_t esgos_dt_system_disable_msc(duk_context *ctx)
{
    esgos_system_usb_msc_end();
    return 0;
}
duk_ret_t esgos_dt_system_check_msc(duk_context *ctx)
{
    duk_push_boolean(ctx, esgos_system_usb_msc_is_started());
    return 1;
}
static handler to_settings = nullptr;
duk_ret_t esgos_dt_system_to_settings(duk_context *ctx)
{
    if (to_settings != nullptr)
    {
        to_settings();
    }
    return 0;
}
void esgos_dt_set_to_settings(handler handler)
{
    to_settings = handler;
}
void esgos_dt_bind_system(duk_context *ctx)
{
    duk_push_global_object(ctx);
    duk_push_object(ctx);
    duk_put_function_list(ctx, -1, sys_funcs);
    duk_put_prop_string(ctx, -2, "System");
    duk_pop(ctx);
}