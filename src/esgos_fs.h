#ifndef __ESGOS_FS_H__
#define __ESGOS_FS_H__
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <M5Unified.h>

bool esgos_fs_init();
void *esgos_fs_open(const char *fp,const char *mode);
size_t esgos_fs_size(void *file_handle);
size_t esgos_fs_seek(void *file_handle, size_t pos);
bool esgos_fs_is_exists(const char *fp);
bool esgos_fs_is_directory(const char *fp);
bool esgos_fs_remove(const char *fp);
void *esgos_fs_open_next_file(void *handle);
void esgos_fs_close(void *handle);
int esgos_fs_read_char(void* handle);
size_t esgos_fs_get_pos(void *file_handle);
char *esgos_fs_read_all_cstr(void *file_handle);
char *esgos_fs_read_file_path_all_cstr(const char *file_name);
/**
 * @brief Must free ptr returned after use!
 */
char *esgos_fs_read_line(void *file_handle);
#endif