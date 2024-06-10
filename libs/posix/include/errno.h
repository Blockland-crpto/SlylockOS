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
#ifndef __ERRNO_H
#define __ERRNO_H

#include <libdebug.h>

//slylock only feature
#define errnoset(erno, msg, ret) \
	dlog(msg); \
	errno = erno; \
	return ret;

#define EACCES 1
#define EDOM 2
#define EILSEQ 3
#define ERANGE 4
#define EBADF 5
#define EIO 6
#define EINVAL 7
#define EFBIG 8
#define EINTR 9
#define ENOSPC 10
#define ENOMEM 11
#define EMFILE 12
#define EOVERFLOW 13
#define EISDIR 14
#define ENAMETOOLONG 15
#define ENFILE 16
#define ENOENT 17
#define ENOTDIR 18

int errno;

void errno_init();

#endif