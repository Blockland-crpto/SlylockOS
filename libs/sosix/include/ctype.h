#ifndef __CTYPE_H
#define __CTYPE_H

#if defined(__cplusplus)
extern "C" {
#endif

	int isdigit(char c);
	int isspace(char c);
	int isalnum(int c);
	int tolower(int c);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif