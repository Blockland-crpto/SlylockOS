#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <libssp.h>

int fprintf(FILE* stream, const char *format, ...) {
	va_list ap;
	va_start(ap, format);

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
					fputs(va_arg(ap, const char *), stream);
					break;
				} case 'd': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 10);
					fputs(str, stream);
					break;
				} case 'x':
					num = va_arg(ap, int);
					str = itoa(num, buf, 16);
					fputs(str, stream);
					break;
				default: {
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