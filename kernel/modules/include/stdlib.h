#ifndef __STDLIB_H
#define __STDLIB_H

#include <system/task.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 32767

int rand(void);

void srand(unsigned int seed);

void *malloc(long numbytes);

__attribute__((__noreturn__)) 
void abort(void);


#endif