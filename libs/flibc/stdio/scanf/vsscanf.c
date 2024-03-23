#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

static int my_sscanf_int(const char **str, int *result) {
	int value = 0;
	int sign = 1;

	// Check for sign
	if (**str == '-') {
		sign = -1;
		(*str)++;  // Move past sign character
	}

	// Read digits
	while (isdigit(**str)) {
		value = value * 10 + (**str - '0');
		(*str)++;  // Move to next character in input string
	}

	*result = value * sign;
	return 1;  // Successfully read an integer
}

static int my_sscanf_string(const char **str, char *result) {
	int count = 0;

	// Skip leading whitespace
	while (isspace(**str)) {
		(*str)++;  // Move to next character in input string
	}

	// Read characters until whitespace
	while (**str != '\0' && !isspace(**str)) {
		*result++ = **str;
		(*str)++;  // Move to next character in input string
		count++;
	}

	// Null-terminate the string
	*result = '\0';

	return count > 0 ? 1 : 0;  // Successfully read a string if count > 0
}

int vsscanf(const char *restrict str, const char *restrict format, va_list args) {
	int count = 0; // Number of successfully matched and assigned input items
	const char *ptr = format;

	while (*ptr != '\0' && *str != '\0') {
		if (*ptr != '%') {
			// Regular character, match with input string
			if (*str != *ptr) {
				break;  // Failed to match, stop scanning
			}
			str++;  // Move to next character in input string
		} else {
			// Format specifier, process accordingly
			ptr++;  // Move past '%'
			if (*ptr == 'd') {
				// Integer conversion
				int *arg = va_arg(args, int*);
				if (my_sscanf_int(&str, arg) != 1) {
					break;  // Failed to read integer, stop scanning
				}
				count++;
			} else if (*ptr == 's') {
				// String conversion
				char *arg = va_arg(args, char*);
				if (my_sscanf_string(&str, arg) != 1) {
					break;  // Failed to read string, stop scanning
				}
				count++;
			} else if (*ptr == 'c') {
				// Character conversion
				char *arg = va_arg(args, char*);
				*arg = *str;
				str++;  // Move to next character in input string
				count++;
			}
			// Add more format specifiers as needed
		}
		ptr++;  // Move to next format specifier or character in format string
	}

	va_end(args);
	return count;
}
