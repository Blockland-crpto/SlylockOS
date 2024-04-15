#ifndef __LIBRTC_H
#define __LIBRTC_H

#define CURRENT_YEAR        2023


#if defined(__cplusplus)
extern "C" {
#endif
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


#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif