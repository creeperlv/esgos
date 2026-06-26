#ifndef __ESGOS_SYSTEM_USB_H__
#define __ESGOS_SYSTEM_USB_H__


#include <Arduino.h>
#include <SD.h>
#include <M5Unified.h>
#include <M5GFX.h>
#include <USB.h>
#include <USBMSC.h>
#include "esgos_core.h"

void esgos_system_usb_msc_start();
bool esgos_system_usb_msc_is_started();
void esgos_system_usb_msc_end();

#endif