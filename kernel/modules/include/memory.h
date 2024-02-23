/**
  \file      memory.h
  \brief     Memory support.
  \details   This header file is used for memory allocation/freeing/etc. support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __MEM_H
#define __MEM_H



/**
	\brief Gets RAM installed

	Gets the amount of RAM installed in the computer.
*/
int ram_size();


/**
  \typedef unsigned long uintptr_t
  \brief Defines a unsigned long for uintptr_t
*/
typedef unsigned long uintptr_t;
/**
  \typedef long intptr_t
  \brief Defines a long for intptr_t
*/
typedef long intptr_t;


// unused, I think
void *sbrk(intptr_t incr);

/**
  \brief Initializes malloc function
*/
void malloc_init();

/**
  \brief Frees the memory of *firstbyte
*/
void free(void *firstbyte);
/**
  \brief Allocates memory with the size being numbytes
*/
void *malloc(long numbytes);

#endif