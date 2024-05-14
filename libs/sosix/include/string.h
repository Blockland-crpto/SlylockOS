/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
//string.h implementation

#ifndef __STRING_H
#define __STRING_H


#if defined(__cplusplus)
extern "C" {
#endif
	#include <stddef.h>
	#include <locale.h>

	//protected mem modes
	enum protected_mem_modes {
		MODE_NONE_ONLY = 0,
		MODE_READ_ONLY = 1,
		MODE_WRITE_ONLY = 2,
		MODE_READ_WRITE = 3,
	};
	
	//protected mem blocks structure
	typedef struct {
		void* address;
		enum protected_mem_modes mode;
	} protected_mem_block_t;

	//array of blacklisted mem blocks
	protected_mem_block_t protected_mem_blocks[100];

	//memccpy implementation
	void *memccpy(void *restrict s1, const void *restrict s2, int c, size_t n);

	//memchr implementation
	void *memchr(const void *s, int c, size_t n);

	//memcmp implementation
	int memcmp(const void *s1, const void *s2, size_t n);

	//memcpy implementation
	void *memcpy(void *restrict s1, const void *restrict s2, size_t n);

	//memmove implementation
	void *memmove(void *s1, const void *s2, size_t n);

	//memset implementation
	void *memset(void *s, int c, size_t n);

	//stpcpy implementation
	char *stpcpy(char *restrict s1, const char *restrict s2);

	//stpncpy implementation
	char *stpncpy(char *restrict s1, const char *restrict s2, size_t n);

	//strcat implementation
	char *strcat(char *restrict s1, const char *restrict s2);

	//strchr implementation
	char *strchr(const char *s, int c);

	//strcmp implementation
	int strcmp(const char *s1, const char *s2);

	//strcoll implementation
	int strcoll(const char *s1, const char *s2);

	//strcoll_l implementation
	int strcoll_l(const char *s1, const char *s2, locale_t locale);

	//strcpy implementation
	char *strcpy(char *restrict s1, const char *restrict s2);

	//strcspn implementation
	size_t strcspn(const char *s1, const char *s2);

	//strdup implementation
	char *strdup(const char *s);

	//strerror implementation
	char *strerror(int errnum);

	//strerror_l implementation
	char *strerror_l(int errnum, locale_t locale);

	//strerror_r implementation
	int strerror_r(int errnum, char* strerrbuf, size_t buflen);

	//strlen implementation
	size_t strlen(const char *s);

	//strncat implementation
	char *strncat(char* restrict s1, const char* restrict s2, size_t n);

	//strncmp implementation
	int strncmp(const char *s1, const char *s2, size_t n);

	//strncpy implementation
	char *strncpy(char *restrict s1, const char *restrict s2, size_t n);
	
	//strndup implementation
	char *strndup(const char *s, size_t size);

	//strnlen implementation
	size_t strnlen(const char *s, size_t maxlen);

	//strpbrk implementation
	char *strpbrk(const char *s1, const char *s2);
	
	//strrchr implementation
	char *strrchr(const char *s, int c);
	
	//strsignal implementation
	char *strsignal(int signum);

	//strspn implementation
	size_t strspn(const char *s1, const char *s2);

	//strstr implementation
	char* strstr(const char *s1, const char *s2);

	//strtok implementation
	char *strtok(char *restrict s, const char *restrict sep);

	//strtok_r implementation
	char *strtok_r(char *restrict s, const char *restrict sep, char **restrict state);

	//strxfrm implementation
	size_t strxfrm(char *restrict s1, const char *restrict s2, size_t n);

	//strxfrm_l implementation
	size_t strxfrm_l(char *restrict s1, const char *restrict s2, size_t n, locale_t locale);

	//exclusive security functions
	//memblklst - a function that blacklists a memory block from being modified
	void* memprotect(const void *s, enum protected_mem_modes mode);

	//memcheck - a function that checks if a memory block is blacklisted
	enum protected_mem_modes memcheck(const void *s);
	
	//Exclusive flibc helper functions:
	void swap(char *x, char *y);
	char* reverse(char *buffer, int i, int j);
	int starts_with(char* starts, char* s);
	char* itoa(int num, char* str, int base);
	int octtodec(int n);
	unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
	char* rstrstr(const char *str, const char *sub);
	int *create_delim_dict(int *delim);
	
#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
