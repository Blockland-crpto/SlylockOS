#include <stddef.h>
#include <stdbool.h>

static char *strtok_state;

char *strtok(char *restrict s, const char *restrict sep) {
	if (s == NULL && (s = strtok_state) == NULL) return NULL;
	size_t skip_len = strspn(s, sep);
	s += skip_len;
	if (*s == '\0') return NULL;
	char *token_start = s;
	size_t token_len = strcspn(s, sep);
	s += token_len;
	if (*s != '\0') *s++ = '\0';
	strtok_state = s;
	return token_start;
}
