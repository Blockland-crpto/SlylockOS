#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <libssp.h>

int vprintf(const char *format, va_list ap) {
	const char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++; 			
			char buf[256];
			switch (*ptr++) {
				case 's': {
					fprintf(stdout, va_arg(ap, const char *));
					break;
				} case 'd': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 10);
					fprintf(stdout, str);
					break;
				} case 'x': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 16);
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