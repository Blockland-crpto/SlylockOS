#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <libssp.h>

int vfprintf(FILE* stream, const char *format, va_list ap) {
	const char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			switch (*ptr++) {
				case 's': {
					fputs(va_arg(ap, const char *), stream);
					break;
				} case 'd': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 10);
					fputs(str, stream);
					break;
				} case 'x': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 16);
					fputs(str, stream);
					break;
				} default: {
					return -1;
				}
			}
		} else {
			fputc(*ptr++, stream);
		}
		len++;
	}

	va_end(ap);
	return len;
}