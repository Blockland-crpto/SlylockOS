#include <stdio.h>
#include <stdarg.h>

int scanf(const char *restrict format, ...) {
	va_list args;
	va_start(args, format);

	int result = fscanf(stdin, format, args);

	va_end(args);

	return result;
}