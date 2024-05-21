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
/**
  \file      memory.h
  \brief     Memory support.
  \details   This header file is used for memory allocation/freeing/etc. support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __LIBMEM_H
#define __LIBMEM_H



#if defined(__cplusplus)
extern "C" {
#endif

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
	

	typedef struct mem_control_block {
		int is_available;
		int size;
	} mem_control_block;

	//a posix memaligned control block
	typedef struct mem_aligned_ctrl_block {
		void* pad_address;
		void* mem_address;
	} mem_aligned_ctrl_block;
	

	#define asizeof(x) ((char *)(&x + 1) - (char *)&x)
	
	/**
		\brief Gets RAM installed

		Gets the amount of RAM installed in the computer.
	*/
	int ram_size();





	// unused, I think
	void *sbrk(intptr_t incr);

	/**
	  \brief Initializes kalloc function
	*/
	void kalloc_init();

	/**
	  \brief Frees the memory of *firstbyte
	*/
	void kfree(void *firstbyte);
	/**
	  \brief Allocates memory with the size being numbytes
	*/
	 __attribute__ ((malloc, alloc_size(1))) void *kalloc(long numbytes);

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif