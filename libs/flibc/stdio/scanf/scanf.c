#include <stdio.h>
#include <stdarg.h>

int scanf(const char *restrict format, ...) {
	va_list args;
	va_start(args, format);

	va_list args_copy;
	va_copy(args_copy, args);  // Create a copy of the va_list

	int result = fscanf(stdin, format, args_copy);

	va_end(args_copy);  // Clean up the copy
	va_end(args);       // Clean up the original

	return result;
}
