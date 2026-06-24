#ifndef __CORE_H__
#define __CORE_H__

#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <Update.h>
#include "esgos_fs.h"
#define ESGOS_VERSION_MAJOR 0
#define ESGOS_VERSION_MINOR 0
#define ESGOS_VERSION_BUILD 0
#define ESGOS_VERSION_PATCH 0

#define ESGOS_RELEASE "Dev"

#define STRINGIFY(x) TOSTRING(x)
#define TOSTRING(x) #x
#include <stdint.h>
typedef struct esgos_config
{
    bool release_sys_app;

} esgos_config;
void show_logln(const char *str);
void *esgos_obtain_null();
const char *esgos_version();
const char *esgos_release_channel();
bool esgos_is_show_boot_log();
bool esgos_is_rom_update_scheduled();
typedef enum esgos_update_result
{
    esgos_update_success,
    esgos_update_file_not_exist,
    esgos_update_not_file,
    esgos_update_file_empty,
    esgos_update_unknown,
    esgos_update_not_enough_space,
    esgos_update_partial_written,
} esgos_update_result;
esgos_update_result esgos_core_update(char *file);
void esgos_schedule_rom_update();
void esgos_apply_rom_update();
void esgos_poweroff();
void esgos_restart();
#endif