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
#include <libc.h>
#include <libmodule.h>
#include <libmem.h>

void libc_init() {
	module_t modules_libc = MODULE("kernel.modules.libc", "Defines the C standard library from http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf for convenient use.");
	INIT(modules_libc);
	errno_init();
	
	stdin = (FILE*)kalloc(sizeof(FILE));
	stdin->stream = (uint8_t*)kalloc(BUFSIZ);

	stdout = (FILE*)kalloc(sizeof(FILE));
	stdout->stream = (uint8_t*)kalloc(BUFSIZ);

	stderr = (FILE*)kalloc(sizeof(FILE));
	stderr->stream = (uint8_t*)kalloc(BUFSIZ);
	
	DONE(modules_libc);
}