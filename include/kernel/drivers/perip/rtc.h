#ifndef __DRIVERS_PERIP_RTC_H
#define __DRIVERS_PERIP_RTC_H

#define CURRENT_YEAR        2023



unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned int year;

int get_update_in_progress_flag();
unsigned char get_RTC_register(int reg);
void read_rtc();
void rtc_init();

#endif