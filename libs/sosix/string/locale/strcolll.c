#include <string.h>
#include <locale.h>

int strcoll_l(const char *s1, const char *s2, locale_t locale) {
	//todo: implement actual locale info
	return strcmp(s1, s2);
}