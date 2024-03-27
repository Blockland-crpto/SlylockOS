#include <system/debug.h>
#include <libvga.h>
#include <libssp.h>


void warn(char* reason) {
	putstr("WARN: ", COLOR_RED, COLOR_BLK);
	putstr(reason, COLOR_WHT, COLOR_BLK);
	putstr("\n", COLOR_WHT, COLOR_BLK);
}