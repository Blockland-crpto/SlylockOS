#ifndef __STDLIB_H
#define __STDLIB_H

#if defined(__cplusplus)
extern "C" {
#endif

	#include <libfs.h>
	#include <sys/wait.h>
	#include <stdint.h>
	#include <stddef.h>
	
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

	unsigned short _rand48_seed[3];

	//functions to run at exit
	void (*runAtExit[32])();
	
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
	int grantpt(fs_node_t* node);

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

	//TODO: add MBLen, mbtowc, mbstowcs


	//mkdtemp implementation
	char *mkdtemp(char *temp);
	
	//strtod implementation
	double strtod(const char *restrict nptr, char **restrict endptr);

	//strtol implmentation
	long strtol(const char *restrict str, char **restrict endptr, int base);

	//strtoll implementation
	long long strtoll(const char *restrict str, char **restrict endptr, int base);
	/*
	int rand(void);
	
	
	void srand(unsigned int seed);
	
	void *realloc(void *ptr, long numbytes);
	
	
	*/

#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif