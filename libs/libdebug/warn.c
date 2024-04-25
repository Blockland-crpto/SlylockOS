/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libdebug.h>
#include <libvga.h>
#include <libssp.h>
#include <libserial.h>
#include <libtimer.h>
#include <string.h>
#include <stdarg.h>
#include <system/types.h>


void warn(char* reason) {
	putstr("[", COLOR_WHT, COLOR_BLK);
	putstr("WARN", COLOR_YEL, COLOR_BLK);
	putstr("]: ", COLOR_WHT, COLOR_BLK);
	putstr(reason, COLOR_WHT, COLOR_BLK);
}

//function to log info to serial console
int slog(const char *format, ...) {
	va_list ap;
	va_start(ap, format);
	char buffer[256];

	char* time = itoa(get_tracked_seconds(), buffer, 10);

	serial_write_string("[LOG @ ");
	serial_write_string(time);
	serial_write_string("]: ");

	char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			int num;
			char* str;
			switch (*ptr++) {
				case 's': {
					serial_write_string(va_arg(ap, const char *));
					break;
				} case 'd': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 10);
					serial_write_string(str);
					break;
				} case 'x':
					num = va_arg(ap, int);
					str = itoa(num, buf, 16);
					serial_write_string(str);
					break;
				default: {
					return -1;
				}
			}
		} else {
			serial_write_char(*ptr++);
		}
		len++;
	}

	serial_write_string("\n");
	va_end(ap);
	return len;
}