#include <string.h>
#include <stddef.h>

char *strremove(char *str, const char *sub) {
	char *p, *q, *r;
	if ((q = r = strstr(str, sub)) != NULL) {
		int len = strlen(sub);
		while ((r = strstr(p = r + len, sub)) != NULL) {
			while (p < r)
				*q++ = *p++;
		}
		while ((*q++ = *p++) != '\0')
			continue;
	}
	return str;
}