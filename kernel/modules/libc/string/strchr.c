#include <string.h>
#include <stddef.h>


const char* strchr(const char* s, int c) {
	if (s == NULL) {
		return NULL;
	}
	if ((c > 255) || (c < 0)) {
		return NULL;
	}
	int s_len;
	int i;
	s_len = strlen(s);
	for (i = 0; i < s_len; i++) {
		if ((char) c == s[i]) {
			return (const char*) &s[i];
		}
	}
	return NULL;
}