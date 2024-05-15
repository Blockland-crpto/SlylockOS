#include <string.h>
#include <stddef.h>
 

void *memmove(void *s1, const void *s2, size_t n) {
	unsigned char *d = s1;
	const unsigned char *s = s2;

	if (d == s) {
		return d;
	}

	if (s + n <= d || d + n <= s) {
		return memcpy(d, s, n);
	}

	if (d < s) {
		for (size_t i = 0; i < n; ++i) {
			d[i] = s[i];
		}
	} else {
		for (size_t i = n; i != 0; --i) {
			d[i-1] = s[i-1];
		}
	}

	return d;
}