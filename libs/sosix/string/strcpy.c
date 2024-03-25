#include <string.h>
#include <stddef.h>
#include <libssp.h>

char *strcpy(char *restrict s1, const char *restrict s2) {
	// return if no memory is allocated to the destination
	if (s1 == NULL) {
		return NULL;
	}

	// take a pointer pointing to the beginning of the destination string
	char *ptr = s1;

	// copy the C-string pointed by source into the array
	// pointed by destination
	while (*s2 != '\0')
	{
		*s1 = *s2;
		s1++;
		s2++;
	}

	// include the terminating null character
	*s1 = '\0';

	// the destination is returned by standard `strcpy()`
	return ptr;
}