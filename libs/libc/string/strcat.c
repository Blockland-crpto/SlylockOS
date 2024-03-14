#include <string.h>


char* strcat(char* destination, const char* source)
{
	// make `ptr` point to the end of the destination string
	char* ptr = destination + strlen(destination);

	// appends characters of the source to the destination string
	while (*source != '\0') {
		*ptr++ = *source++;
	}

	// null terminate destination string
	*ptr = '\0';

	// the destination is returned by standard `strcat()`
	return destination;
}