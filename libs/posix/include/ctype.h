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
#ifndef __CTYPE_H
#define __CTYPE_H

#if defined(__cplusplus)
extern "C" {
#endif

	//for posix standard
	typedef void *locale_t;
	
	int isalnum(int c);
	int isalnum_l(int c, locale_t locale);
	int isalpha(int c);
	int isalpha_l(int c, locale_t locale);
	int isascii(int c);
	int isblank(int c);
	int isblank_l(int c, locale_t locale);
	int iscntrl(int c);
	int iscntrl_l(int c, locale_t locale);
	int isdigit(char c);
	int isspace(char c);
	
	int tolower(int c);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif