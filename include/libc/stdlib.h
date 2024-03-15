#ifndef __STDLIB_H
#define __STDLIB_H

#if defined(__cplusplus)
extern "C" {
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

//Note: by default, the Fast LIB C library enables all data types provided by GNU
//the Div type as seen in GNU C LIB
typedef struct {
	int quot;
	int rem;
} div_t;

//the same type but with long ints
typedef struct {
	long int quot;
	long int rem;
} ldiv_t;

/**
	\brief Gets a random number
	\returns The random number
*/
int rand(void);
/**
	\brief returns the absolute value of an integer
	\param{in} i The value to retrieve ABS for
	\returns The absolute value
*/
int abs(int i);
/**
	\brief Converts a string to a integer
	\param{in} str The string to convert
	\returns The converted integer
*/
int atoi(char* str);
/**
	\brief Converts a string to a long integer
	\param{in} str The string to convert
	\returns The converted long integer
*/
long int a64l(const char *str);
/**
	\brief Makes a div representation of a div data type
	\param{in} numer The numerator
	\param{in} denom The denominator
	\returns The div representation
*/
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