#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <libssp.h>

long long strtoll(const char *restrict str, char **restrict endptr, int base) {
	long long result = 0;
	bool negative = false;

	// Skip leading whitespace
	while (isspace(*str)) {
		str++;
	}

	// Check for sign
	if (*str == '-') {
		negative = true;
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

	return negative ? -result : result;
}