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
  \file      ports.h
  \brief     Provides inb/outb/etc. support for the kernel, generally ports
  \details   Allows the kernel to inportbyte, outportbyte and similar.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __LIBPORTS_H
#define __LIBPORTS_H

#include <system/types.h>

#if defined(__cplusplus)
extern "C" {
#endif
	/**
		\brief In port byte function for ports

		Executes an in port byte call in inline assembly (`inb`).
	*/
	extern unsigned char inb(unsigned short port);
	/**
		\brief Out port byte function for ports

		Executes an out port byte call in inline assembly (`outb`).
	*/
	extern void outb(unsigned short port, unsigned char data);

	/**
		\brief In port word function for ports

		Executes an in port word call in inline assembly (`inw`).
	*/
	extern uint16_t inw(uint16_t port);
	/**
		\brief Out port word function for ports

		Executes an out port word call in inline assembly (`outw`).
	*/
	extern void outw(uint16_t port, uint16_t val);

	/**
		\brief In port long function for ports

		Executes an in port long call in inline assembly (`inl`).
	*/
	extern uint32_t inl(uint16_t port);
	/**
		\brief Out port long function for ports

		Executes an out port long call in inline assembly (`outl`).
	*/
	extern void outl(uint16_t port, uint32_t val);

	extern void io_wait(int iters);


#if defined(__cplusplus)
} /* extern "C" */
#endif




#endif