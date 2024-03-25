#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)) {
	const char *ptr = (const char *)base;
	size_t left = 0;
	size_t right = nel - 1;

	while (left <= right) {
		size_t mid = left + (right - left) / 2;
		const char *midptr = ptr + mid * width;
		int cmp = compar(key, midptr);

		if (cmp == 0) {
			return (void *)midptr;
		} else if (cmp < 0) {
			right = mid - 1;
		} else {
			left = mid + 1;
		}
	}

	return NULL;
}