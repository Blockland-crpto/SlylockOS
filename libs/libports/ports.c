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
#include <libports.h>
#include <stdint.h>
#include <stdbool.h>
 

unsigned char inb(unsigned short port){
    unsigned char result;
    __asm__ volatile("inb %%dx, %%al": "=a"(result) : "d" (port));

    return result;
}

void outb(unsigned short port, unsigned char data){
	__asm__ volatile("outb %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t inw(uint16_t port) {
 	unsigned char result;
  __asm__ volatile("inw %%dx, %%ax": "=a"(result) : "d" (port));

  return result;
}
void outw(uint16_t port, uint16_t val) {
	asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

uint32_t inl(uint16_t port) {
	unsigned char result;
    __asm__ volatile("inl %%edx, %%eax": "=a"(result) : "d" (port));

    return result;
}
void outl(uint16_t port, uint32_t val) {
	asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
}

void io_wait(int iters) {
	for (int i = 0; i < iters; i++) {
		outb(0x80, 0);
	}
}