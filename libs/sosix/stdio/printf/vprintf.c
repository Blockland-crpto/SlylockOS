#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int vprintf(const char *format, va_list ap) {
	char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			int num;
			char* str;
			char buf[256];
			switch (*ptr++) {
				case 's': {
					fprintf(stdout, va_arg(ap, const char *));
					break;
				} case 'd': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 10);
					fprintf(stdout, str);
					break;
				} case 'x': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 16);
					fprintf(stdout, str);
					break;
				} default: {
					return -1;
				}
			}
		} else {
			fputc((int)*ptr++, stdout);
			len++;
		}
	}

	va_end(ap);
	return len;
}