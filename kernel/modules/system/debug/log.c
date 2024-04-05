#include <system/debug.h>
#include <system/types.h>
#include <libvga.h>
#include <libssp.h>

//function to log info
void log(char* message) {
	putstr("[", COLOR_WHT, COLOR_BLK);
	putstr("LOG",COLOR_DGY, COLOR_BLK);
	putstr("]: ", COLOR_WHT, COLOR_BLK);
	putstr(message, COLOR_WHT, COLOR_BLK);
}