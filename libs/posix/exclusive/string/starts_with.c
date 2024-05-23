#include <string.h>
 

int starts_with(char* starts, char* s) {
	return strstr(s, starts) == s;
}