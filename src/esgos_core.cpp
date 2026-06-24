#include "esgos_core.h"

void *esgos_obtain_null()
{
    return nullptr;
}
const char *esgos_version()
{
    return "" STRINGIFY(ESGOS_VERSION_MAJOR) "." STRINGIFY(ESGOS_VERSION_MINOR) "." STRINGIFY(ESGOS_VERSION_BUILD) "." STRINGIFY(ESGOS_VERSION_PATCH);
}

const char *esgos_release_channel()
{
    return ESGOS_RELEASE;
}

bool esgos_is_show_boot_log()
{
    return esgos_fs_is_exists("/boot/f_show_boot_log");
}

bool esgos_is_rom_update_scheduled()
{
    return esgos_fs_is_exists("/boot/f_rom_update_scheduled") && esgos_fs_is_exists("/updates/rom.tar.gz");
}

void esgos_poweroff()
{
    M5.Power.powerOff();
}
void esgos_restart()
{
    ESP.restart();
}
esgos_update_result esgos_core_update(char *file)
{
    if (!esgos_fs_is_exists(file))
    {
        return esgos_update_file_not_exist;
    }
    if (esgos_fs_is_directory(file))
    {
        return esgos_update_not_file;
    }
    File updateSource = SD.open("/update.bin");
    size_t updateSize = updateSource.size();

    esgos_update_result result = esgos_update_unknown;
    if (updateSize > 0)
    {
    }
    else
    {
        result = esgos_update_file_empty;
        goto FINISH;
    }
    if (Update.begin(updateSize))
    {
        size_t written = Update.writeStream(updateSource);
        if (written == updateSize)
        {
            // Serial.println("Written : " + String(written) + " successfully");
        }
        else
        {
            // Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
        }
        if (Update.end())
        {
            result = esgos_update_success;
            goto FINISH;
        }
        else
        {
            goto FINISH;
        }
    }
    else
    {
        // Serial.println("Not enough space to begin OTA");
        result = esgos_update_not_enough_space;
    }
FINISH:
    updateSource.close();
    return result;
}