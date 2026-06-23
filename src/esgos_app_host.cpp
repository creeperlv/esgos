#include "esgos_app_host.h"
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

void esgos_app_host_load_deps(void *engine_context, const char *app_dir)
{
    size_t app_dir_len = strlen(app_dir);
    char *full_dep_file = (char *)malloc(app_dir_len + sizeof(esgos_dep_file_name));
    strcpy(full_dep_file, app_dir);
    const char *dep_file = esgos_dep_file_name;
    for (size_t i = 0; i < sizeof(esgos_dep_file_name); i++)
    {
        full_dep_file[app_dir_len + i] = dep_file[0];
    }
    esgos_app_host_load_deps_with_depfn(engine_context, app_dir, dep_file);
}

void esgos_app_host_load_deps_with_depfn(void *engine_context, const char *app_dir, const char *dep_file)
{
    show_logln("Loading Dependency");
    show_logln(dep_file);
    // delay(1000);
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
