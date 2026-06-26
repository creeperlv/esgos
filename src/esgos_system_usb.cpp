#include "esgos_system_usb.h"

static int32_t onWrite(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize)
{
    uint32_t secSize = SD.sectorSize();
    if (!secSize)
    {
        return false; // disk error
    }
    // log_v("Write lba: %ld\toffset: %ld\tbufsize: %ld", lba, offset, bufsize);
    for (int x = 0; x < bufsize / secSize; x++)
    {
        uint8_t blkbuffer[secSize];
        memcpy(blkbuffer, (uint8_t *)buffer + secSize * x, secSize);
        if (!SD.writeRAW(blkbuffer, lba + x))
        {
            return false;
        }
    }
    return bufsize;
}

static int32_t onRead(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize)
{
    uint32_t secSize = SD.sectorSize();
    if (!secSize)
    {
        return false; // disk error
    }
    // log_v("Read lba: %ld\toffset: %ld\tbufsize: %ld\tsector: %lu", lba, offset, bufsize, secSize);
    for (int x = 0; x < bufsize / secSize; x++)
    {
        if (!SD.readRAW((uint8_t *)buffer + (x * secSize), lba + x))
        {
            return false; // outside of volume boundary
        }
    }
    return bufsize;
}

static bool onStartStop(uint8_t power_condition, bool start, bool load_eject)
{
    // log_i("Start/Stop power: %u\tstart: %d\teject: %d", power_condition, start, load_eject);
    return true;
}
static void usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == ARDUINO_USB_EVENTS)
    {
        arduino_usb_event_data_t *data = (arduino_usb_event_data_t *)event_data;

        switch (event_id)
        {
        case ARDUINO_USB_STARTED_EVENT:
            show_logln("USB PLUGGED");
            break;
        case ARDUINO_USB_STOPPED_EVENT:
            show_logln("USB UNPLUGGED");
            break;
        case ARDUINO_USB_SUSPEND_EVENT:
            show_logln("USB SUSPENDED");
            break;
        case ARDUINO_USB_RESUME_EVENT:
            show_logln("USB RESUMED");
            break;

        default:
            break;
        }
    }
}

static USBMSC msc;
static bool is_started = false;
void esgos_system_usb_msc_start()
{
    msc.vendorID("ESP32");
    msc.productID("USB_MSC");
    msc.productRevision("1.0");
    msc.onRead(onRead);
    msc.onWrite(onWrite);
    msc.onStartStop(onStartStop);
    msc.mediaPresent(true);
    msc.begin(SD.numSectors(), SD.sectorSize());
    USB.begin();
    is_started = true;
}

bool esgos_system_usb_msc_is_started()
{
    return is_started;
}

void esgos_system_usb_msc_end()
{
    msc.mediaPresent(false);
    msc.end();
    is_started = false;
}
