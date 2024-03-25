#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <libssp.h>

double strtod(const char *restrict nptr, char **restrict endptr) {
	double result = 0.0;
	int sign = 1;
	int decimal = 0;
	int exp_sign = 1;
	int exponent = 0;
	const char *str = nptr;

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

	// Parse digits before decimal point
	while (isdigit(*str)) {
		result = result * 10 + (*str - '0');
		str++;
	}

	// Parse decimal point and digits after decimal point
	if (*str == '.') {
		str++;
		while (isdigit(*str)) {
			result = result * 10 + (*str - '0');
			decimal++;
			str++;
		}
	}

	// Parse exponent
	if (*str == 'e' || *str == 'E') {
		str++;
		if (*str == '-') {
			exp_sign = -1;
			str++;
		} else if (*str == '+') {
			str++;
		}
		while (isdigit(*str)) {
			exponent = exponent * 10 + (*str - '0');
			str++;
		}
		exponent *= exp_sign;
	}

	// Adjust result for decimal and exponent
	while (decimal-- > 0) {
		result /= 10;
	}
	while (exponent > 0) {
		result *= 10;
		exponent--;
	}
	while (exponent < 0) {
		result /= 10;
		exponent++;
	}

	// Set endptr if provided
	if (endptr != NULL) {
		*endptr = (char *)str;
	}

	return sign * result;
}