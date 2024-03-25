#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <libssp.h>

int strncmp(const char *s1, const char *s2, size_t n) {
	size_t len = 0;
	int i;
	uint8_t *p1 = (uint8_t*)s1;
	uint8_t *p2 = (uint8_t*)s2;
	for (i = 0; p1[i] == p2[i] && len < n; i++) {
		if (p1[i] == '\0' || len == n-1) return 0;
		len++;
	}
	int *r1 = (int*)p1[i];
	int *r2 = (int*)p2[i];
	return r1[i] - r2[i];
}