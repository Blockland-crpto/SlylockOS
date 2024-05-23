#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
 

long strtol(const char *restrict str, char **restrict endptr, int base) {
	long result = 0;
	int sign = 1;

	// Skip leading whitespace
	while (isspace(*str)) {
		str++;
	}

	// Check for sign
	if (*str == '-') {
		sign = -1;
		str++;
	} else if (*str == '+') {
		str++;
	}

	// Determine base if not provided
	if (base == 0) {
		if (*str == '0') {
			if (*(str + 1) == 'x' || *(str + 1) == 'X') {
				base = 16;
				str += 2;
			} else {
				base = 8;
				str++;
			}
		} else {
			base = 10;
		}
	}

	// Parse digits
	while (isalnum(*str)) {
		int digit;
		if (isdigit(*str)) {
			digit = *str - '0';
		} else {
			digit = tolower(*str) - 'a' + 10;
		}
		if (digit >= base) {
			break;
		}
		result = result * base + digit;
		str++;
	}

	// Set endptr if provided
	if (endptr != NULL) {
		*endptr = (char *)str;
	}

	return sign * result;
}