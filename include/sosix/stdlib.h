#ifndef __STDLIB_H
#define __STDLIB_H

#if defined(__cplusplus)
extern "C" {
#endif

	#include <sys/wait.h>
	#define EXIT_FAILURE 1
	#define EXIT_SUCCESS 0
	
	#define RAND_MAX 32767
	#define MB_CUR_MAX 4
	
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

	void _Exit(int status);
	
	/*
	int rand(void);
	int abs(int i);
	int atoi(char* str);
	long int a64l(const char *str);
	div_t div(int numer, int denom);
	void srand(unsigned int seed);
	void *malloc(long numbytes);
	void *realloc(void *ptr, long numbytes);
	void free(void *ptr);
	__attribute__((__noreturn__)) 
	void abort(void);
	*/

#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif