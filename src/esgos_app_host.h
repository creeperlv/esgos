#ifndef __ESGOS_APP_HOST_H__
#define __ESGOS_APP_HOST_H__
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#define esgos_dep_file_name "/esgos.dep"
#include "esgos_engine.h"
#include "esgos_duktape_funcs.h"
#include "esgos_system_funcs.h"
void esgos_app_host_load_deps(void *engine_context, const char *app_dir);
void esgos_app_host_load_deps_with_depfn(void *engine_context, const char *app_dir, const char *dep_file);
void *esgos_app_host_start_app(const char *app_dir);
void *esgos_app_host_start_system_app(const char *app_dir);
#endif