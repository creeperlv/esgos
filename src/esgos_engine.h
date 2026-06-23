#ifndef __ESGOS_ENGINE__
#define __ESGOS_ENGINE__
#include "esgos_fs.h"
#include "esgos_ui.h"
#include "esgos_core.h"
#include "esgos_duktape_funcs.h"
#include "duktape.h"

typedef void (*esgos_engine_app_stop)(void *);
typedef void (*esgos_launch_app)(const char *);

void *esgos_create_engine_context();
void esgos_destroy_engine_context(void *engine_context);

void esgos_bind_to_home(void (*to_home)());
void esgos_bind_app_stop(esgos_engine_app_stop func);
void esgos_bind_esgos_launch_app(esgos_launch_app func);

void esgos_load_script(void *engine_context, char *script);
void esgos_load_script_no_result(void *engine_context, char *script);
void esgos_load_script_from_file(void *engine_context,const char *file_path);
void esgos_load_script_fn(void *engine_context, char *script, char *fn);
void esgos_load_bytecode(void *engine_context, void *data, size_t data_size);
/**
 * @brief call to a loaded script with return value left on the stack.
 * @param func the function to call, must be a valid emca script statement like "func()"
 */
void esgos_call_func_with_return(void *engine_context, char *func);
void esgos_engine_setup_system_app_api(void *engine_context);
/**
 * @brief call to a loaded script with no return value left on the stack.
 * @param func the function to call, must be a valid emca script statement like "func()"
 */
void esgos_call_func(void *engine_context, char *func);
void esgos_call_init(void *engine_context);
void esgos_call_loop(void *engine_context);
#endif