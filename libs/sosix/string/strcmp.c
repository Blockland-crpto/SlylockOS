#include <string.h>
#include <stdint.h>
#include <libssp.h>

int strcmp(const char *s1, const char *s2) {
	int i;
	uint8_t *p1 = (uint8_t*)s1;
	uint8_t *p2 = (uint8_t*)s2;
	for (i = 0; p1[i] == p2[i]; i++) {
		if (p1[i] == '\0') return 0;
	}
	return p1[i] - p2[i];
}