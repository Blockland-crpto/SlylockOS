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
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <libc.h>
#include <libmodule.h>
#include <libmem.h>
#include <libdebug.h>

//functions to run at exit
extern void (*runAtExit[32])();
extern long int rnext;
extern unsigned long int rrnext;
extern char* cstr;

//it initalizes the OSes C runtime
void libc_init() {
	module_t modules_libc = MODULE("kernel.modules.libc", "Defines the C standard library from http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf for convenient use.");
	INIT(modules_libc);
	errno_init();

	rnext = (long int)kalloc(sizeof(long int));
	rrnext = (unsigned long int)kalloc(sizeof(unsigned long int));

	//lets see if next worked
	if (rnext == 0 || rrnext == 0) {
		//libc failed
		panic("LIBC failed to get enough ram to start", INSUFFICIENT_RAM);
	}
	
	stdin = (FILE*)kalloc(sizeof(FILE));
	stdin->stream = (uint8_t*)kalloc(BUFSIZ);

	//lets see if next worked
	if (stdin == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (stdin)", INSUFFICIENT_RAM);
	}

	//lets see if next worked
	if (stdin->stream == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (stdin stream)", INSUFFICIENT_RAM);
	}
	
	stdout = (FILE*)kalloc(sizeof(FILE));
	stdout->stream = (uint8_t*)kalloc(BUFSIZ);

	//lets see if next worked
	if (stdout == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (stdout)", INSUFFICIENT_RAM);
	}

	//lets see if next worked
	if (stdout->stream == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (stdout stream)", INSUFFICIENT_RAM);
	}

	stderr = (FILE*)kalloc(sizeof(FILE));
	stderr->stream = (uint8_t*)kalloc(BUFSIZ);

	//lets see if next worked
	if (stderr == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (stderr)", INSUFFICIENT_RAM);
	}

	//lets see if next worked
	if (stderr->stream == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (stderr stream)", INSUFFICIENT_RAM);
	}

	cstr = (char*)kalloc(128);

	//lets see if next worked
	if (cstr == NULL) {
		//libc failed
		panic("LIBC failed to get enough ram to start (cstr)", INSUFFICIENT_RAM);
	}

	strcpy(cstr, "/boot/kernel.bin");
	
	DONE(modules_libc);
}