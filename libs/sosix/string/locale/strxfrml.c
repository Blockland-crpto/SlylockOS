#include <string.h>
#include <stddef.h>
#include <locale.h>
 

size_t strxfrm_l(char *restrict s1, const char *restrict s2, size_t n, locale_t locale) {
	//todo: add locale support
	return strxfrm(s1, s2, n);
}