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
#ifndef __STDLIB_H
#define __STDLIB_H

#include <libfs.h>
#include <sys/wait.h>
#include <stdint.h>
#include <stddef.h>
#include <libproc.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767
#define MB_CUR_MAX 1

#define WEXITSTATUS(status) (status)
#define WIFEXITED(status) (status == NULL)
#define WIFSIGNALED(status) (true)
#define WIFSTOPPED(status) (status == PROC_STATUS_YIELDED)
#define WNOHANG 1
#define WSTOPSIG(status) (status)
#define WTERMSIG(status) (status)
#define WUNTRACED 2

#if defined(__cplusplus)
extern "C" {
#endif

	typedef struct {
		int quot;
		int rem;
	} div_t;
	
	typedef struct {
		long int quot;
		long int rem;
	} ldiv_t;

	typedef struct {
		long long int quot;
		long long int rem;
	} lldiv_t;


	typedef int wchar_t;
	typedef unsigned int size_t;
	
	//_Exit implementation
	void _Exit(int status);

	//a64l implementation
	long a64l(const char *str);

	//abort implementation
	void abort(void);

	//abs implementation
	int abs(int i);

	//atexit implementaion
	int atexit(void (*func)(void));

	//atof implementation
	double atof(const char *str);

	//atoi implementation
	int atoi(const char *str);

	//atol implementation
	long atol(const char *nptr);

	//atoll implementation
	long long atoll(const char *nptr);
	
	//bsearch implementation
	void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

	//calloc implementation
	void *calloc(size_t nelem, size_t elsize);

	//div implementation
	div_t div(int numer, int denom);

	//drand48 implementation
	double drand48(void);

	//erand48 implementation
	double erand48(unsigned short xsubi[3]);

	//exit implementation
	void exit(int status);

	//free implementation
	void free(void *ptr);

	//getenv implementation
	char* getenv(const char *name);

	//getsubopt implementation
	int getsubopt(char **optionp, char * const *keylistp, char **valuep);

	//grantpt implementation
	int grantpt(int node);

	//initstate implementation
	char *initstate(unsigned seed, char *state, size_t size);

	//jrand48 implementation
	long jrand48(unsigned short xsubi[3]);

	//l64a implementation
	char *l64a(long value);

	//labs implementation
	long int labs(long int i);

	//lcong48 implementation
	void lcong48(unsigned short param[7]);

	//ldiv implementation
	ldiv_t ldiv(long int numer, long int denom);
	
	//llabs implementation
	long long int llabs(long long int i);

	//lldiv implementation
	lldiv_t lldiv(long long int numer, long long int denom);

	//lrand48 implementation
	long lrand48(void);

	//malloc implementation
	void *malloc(size_t numbytes);

	//mblen implementation
	int mblen(const char *s, size_t n);

	//mbstowcs implementation
	size_t mbstowcs(wchar_t *restrict pwcs, const char *restrict s, size_t n);

	//mbtowc implementation 
	int mbtowc(wchar_t *restrict pwc, const char *restrict s, size_t n);
	
	//mkdtemp implementation
	char *mkdtemp(char *temp);

	//mkstemp implementation
	int mkstemp(char *temp);

	//posix_memalign implementation
	int posix_memalign(void **memptr, size_t alignment, size_t size);

	//posix_openpt implementation
	int posix_openpt(int oflags);

	//ptsname implementation
	char* ptsname(int filedes);

	//putenv implementation
	int putenv(char* string);

	//qsort implementation
	void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *));

	//rand implementation
	int rand(void);

	//rand_r implementation
	int rand_r(unsigned *seed);

	//random implementation
	long random(void);
	
	//realloc implementation
	void *realloc(void *ptr, size_t numbytes);

	//realpath implementation
	char *realpath(const char *restrict file_name, char *restrict resolved_name);

	//seed48 implementation
	unsigned short *seed48(unsigned short seed16v[3]);

	//setenv implementation
	int setenv(const char *envname, const char *envval, int overwrite);

	//setstate implementatin
	char *setstate(char *state);

	//srand implementation
	void srand(unsigned int seed);

	//srand48 implementation
	void srand48(long seed);

	//srandom implementation
	void srandom(unsigned seed);
	
	//strtod implementation
	double strtod(const char *restrict nptr, char **restrict endptr);

	//strtof
	float strtof(const char *restrict nptr, char **restrict endptr);
	
	//strtol implmentation
	long strtol(const char *restrict str, char **restrict endptr, int base);

	//strtold implementation
	long double strtold(const char *restrict nptr, char **restrict endptr);

	//strtoll implementation
	long long strtoll(const char *restrict str, char **restrict endptr, int base);
	
	//strtoul implementation
	unsigned long strtoul(const char *restrict str, char **restrict endptr, int base);

	//strtoull implementation
	unsigned long long strtoull(const char *restrict str, char **restrict endptr, int base);

	//system implmentation
	int system(const char* command);

	//unlockpt implementation
	int unlockpt(int filedes);

	//unsetenv implementation
	int unsetenv(const char *name);

	//wcstombs implementation
	size_t wcstombs(char *restrict s, const wchar_t *restrict pwcs, size_t n);
	
	//wctomb implementation
	int wctomb(char *s, wchar_t wchar);
#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif