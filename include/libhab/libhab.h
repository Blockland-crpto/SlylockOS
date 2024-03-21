#ifndef __LIBHAB_H
#define __LIBHAB_H

#include <drivers/cpu/cpuid.h>
#include <drivers/perip/rtc.h>
#include <drivers/acpi.h>
#include <string.h>

#define ACPI_ENABLED (acpiEnabled ? 1 : 0)
#define NMI_ENABLED (nmi_enabled ? 1 : 0)

#define ARROW_KEY_UP '{'
#define ARROW_KEY_DOWN '}'
#define ARROW_KEY_LEFT '<'
#define ARROW_KEY_RIGHT '>'
#define MENU_KEY '?'
#define ENTER_KEY '\n'

#define RTC_SECOND second
#define RTC_MINUTE minute
#define RTC_HOUR hour
#define RTC_DAY day
#define RTC_MONTH month
#define RTC_YEAR year

#define dbah() detect_bios_area_hardware()


const char * const cpu_vendor_string();

#endif