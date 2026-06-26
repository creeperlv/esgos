#ifndef __ESGOS_SYSTEM_FUNCS_H__
#define __ESGOS_SYSTEM_FUNCS_H__

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <M5Unified.h>
#include <M5GFX.h>
#include "esgos_fs.h"
#include "esgos_ui.h"
#include "esgos_core.h"
#include "duktape.h"
#include "esgos_system_usb.h"
duk_ret_t esgos_dt_system_restart(duk_context *ctx);
duk_ret_t esgos_dt_system_poweroff(duk_context *ctx);
duk_ret_t esgos_dt_system_firmware_update(duk_context *ctx);
duk_ret_t esgos_dt_system_rom_update(duk_context *ctx);
duk_ret_t esgos_dt_system_enable_msc(duk_context *ctx);
duk_ret_t esgos_dt_system_disable_msc(duk_context *ctx);
duk_ret_t esgos_dt_system_check_msc(duk_context *ctx);
duk_ret_t esgos_dt_system_to_settings(duk_context *ctx);
/**
 * Launch system app. Close current one.
 */
duk_ret_t esgos_dt_system_launch_sys_app(duk_context *ctx);
void esgos_dt_set_to_settings(handler handler);
void esgos_dt_bind_system(duk_context *ctx);
#endif