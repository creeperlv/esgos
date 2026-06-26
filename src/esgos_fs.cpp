#include "esgos_fs.h"
#include "esgos_device_config.h"
#include <Arduino.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <Update.h>
#include <M5Unified.h>

bool esgos_fs_init()
{
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
    if (!SD.begin(SD_SPI_CS_PIN, SPI, 25000000))
    {
        return false;
    }
    return true;
}

void *esgos_fs_open(const char *fp,const char *mode)
{
    fs::File file = SD.open(fp, mode);
    if (!file)
    {
        return nullptr;
    }
    fs::File *filePtr = new fs::File(file);

    return static_cast<void *>(filePtr);
}

size_t esgos_fs_size(void *file_handle)
{
    return static_cast<fs::File *>(file_handle)->size();
}

size_t esgos_fs_seek(void *file_handle, size_t pos)
{
    return static_cast<fs::File *>(file_handle)->seek(pos);
}

bool esgos_fs_is_exists(const char *fp)
{
    return SD.exists(fp);
}

bool esgos_fs_is_directory(const char *fp)
{
    if (esgos_fs_is_exists(fp))
    {
        fs::File file = SD.open(fp);
        bool b = false;
        if (file.isDirectory())
        {
            b = true;
        }
        file.close();
        return b;
    }
    return false;
}

bool esgos_fs_remove(const char *fp)
{

    return SD.remove(fp);
}

void *esgos_fs_open_next_file(void *handle)
{

    fs::File *_file = static_cast<fs::File *>(handle);

    fs::File file = _file->openNextFile();
    ;
    if (!file)
    {
        return nullptr;
    }
    fs::File *filePtr = new fs::File(file);

    return static_cast<void *>(filePtr);
}
void esgos_fs_close(void *handle)
{
    if (!handle)
        return;
    fs::File *filePtr = static_cast<fs::File *>(handle);
    filePtr->close();
    delete filePtr;
}

int esgos_fs_read_char(void *handle)
{
    fs::File *filePtr = static_cast<fs::File *>(handle);
    return filePtr->read();
}

size_t esgos_fs_get_pos(void *file_handle)
{
    return static_cast<fs::File *>(file_handle)->position();
}

char *esgos_fs_read_all_cstr(void *file_handle)
{
    fs::File *filePtr = static_cast<fs::File *>(file_handle);
    char *buf = (char *)malloc(filePtr->size() + 1);
    filePtr->read((uint8_t *)buf, filePtr->size());
    buf[filePtr->size()] = 0;
    return buf;
}

char *esgos_fs_read_file_path_all_cstr(const char *file_name)
{
    void *f_ptr = esgos_fs_open(file_name, "r");
    char *str = esgos_fs_read_all_cstr(f_ptr);
    esgos_fs_close(f_ptr);
    return str;
}

char *esgos_fs_read_line(void *file_handle)
{
    fs::File *filePtr = static_cast<fs::File *>(file_handle);
    char *buf = (char *)malloc(64);
    int count = 0;
    int size = 64;
    while (1)
    {
        auto c = filePtr->read();
        if (c != EOF)
        {
            if (c == '\n' && count > 0)
            {
                goto post_process;
            }
            else
            {
                if (c == '\r')
                    continue;
                buf[count] = c;
                count++;
                if (count >= size)
                {
                    buf = (char *)realloc((void *)buf, size + 64);
                    size += 64;
                }
            }
        }else{
            break;
        }
    }
post_process:
    if (count == 0)
    {
        free((void *)buf);
        return nullptr;
    }
    else
    {
        buf = (char *)realloc(buf, count + 1);
        buf[count] = 0;
    }
    return buf;
}
