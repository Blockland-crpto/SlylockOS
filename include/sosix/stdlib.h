#ifndef __STDLIB_H
#define __STDLIB_H

#if defined(__cplusplus)
extern "C" {
#endif

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
	
	
	int rand(void);
	int abs(int i);
	int atoi(char* str);
	long int a64l(const char *str);
	div_t div(int numer, int denom);
	/**
		\brief sets the seed for the next random number
		\param{in} seed The seed
		\returns Nothing
	*/
	void srand(unsigned int seed);
	/**
		\brief allocates memory dynamicly
		\param{in} numbytes The size to allocate
		\returns the allocated memory address
	*/
	void *malloc(long numbytes);
	/**
		\brief reallocates memory dynamicly
		\param{in} ptr The pointer to reallocate
		\param{in} numbytes The new size
		\returns The random number
	*/
	void *realloc(void *ptr, long numbytes);
	/**
		\brief frees memory dynamicly
		\param{in} ptr The pointer to free
		\returns The random number
	*/
	void free(void *ptr);
	
	__attribute__((__noreturn__)) 
	void abort(void);

#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif