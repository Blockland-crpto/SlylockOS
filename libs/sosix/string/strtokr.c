#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <libssp.h>

char *strtok_r(char *restrict s, const char *restrict sep, char **restrict state) {
	char *token_start;
	if (s == NULL) {
		s = *state;
		if (s == NULL) {
			return NULL;
		}
	}

	s += strspn(s, sep);  // Skip leading separators
	if (*s == '\0') {
		*state = NULL;
		return NULL;
	}

	token_start = s;
	s += strcspn(s, sep);  // Find end of token
	if (*s != '\0') {
		*s++ = '\0';  // Null-terminate the token and move to the next character
	}

	*state = s;  // Save the state for the next call
	return token_start;
}
