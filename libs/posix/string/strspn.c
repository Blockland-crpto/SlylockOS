#include <string.h>
#include <stddef.h>
 

size_t strspn(const char *s1, const char *s2) {
	const char *p;
	const char *a;
	size_t count = 0;

	for (p = s1; *p != '\0'; ++p) {
		for (a = s2; *a != '\0'; ++a)
			if (*p == *a)
				break;
		if (*a == '\0')
			return count;
		else
			++count;
	}
	return count;
}