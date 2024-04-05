#include <system/debug.h>
#include <libvga.h>
#include <libssp.h>


void warn(char* reason) {
	putstr("[", COLOR_WHT, COLOR_BLK);
	putstr("WARN", COLOR_YEL, COLOR_BLK);
	putstr("]: ", COLOR_WHT, COLOR_BLK);
	putstr(reason, COLOR_WHT, COLOR_BLK);
}