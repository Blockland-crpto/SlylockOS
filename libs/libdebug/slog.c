#include <libdebug.h>
#include <system/types.h>
#include <libvga.h>
#include <libssp.h>
#include <libserial.h>
#include <libtimer.h>
#include <string.h>
#include <stdarg.h>

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