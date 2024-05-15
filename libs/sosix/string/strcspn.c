#include <string.h>
#include <stddef.h>
 

 size_t strcspn(const char *s1, const char *s2) {
	size_t len = 0;

	if((s1 == NULL) || (s2 == NULL)) {
		return len;
	}

	while(*s1) {
		if(strchr(s2,*s1)) {
			return len;
		} else {
			s1++;
			len++;
		}
	}
	return len;
}