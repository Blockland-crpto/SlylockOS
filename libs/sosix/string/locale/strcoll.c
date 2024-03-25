#include <string.h>
#include <libssp.h>

int strcoll(const char *s1, const char *s2) {
	//todo: implement actual locale inf
	return strcmp(s1, s2);
}