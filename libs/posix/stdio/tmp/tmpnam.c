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
#include <stdio.h>
#include <string.h>
 

char *tmpnam(char *s) {
	fs_node_t *exists0 = finddir_fs(fs_root, "tmpfile0");
	if (exists0 == NULL) {
		strcat(s, "tmpfile0");
		return s; 
	}
	fs_node_t *exists1 = finddir_fs(fs_root, "tmpfile1");
	if (exists1 == NULL) {
		strcat(s, "tmpfile1");
		return s; 
	}
	fs_node_t *exists2 = finddir_fs(fs_root, "tmpfile2");
	if (exists2 == NULL) {
		strcat(s, "tmpfile2");
		return s; 
	}
	fs_node_t *exists3 = finddir_fs(fs_root, "tmpfile3");
	if (exists3 == NULL) {
		strcat(s, "tmpfile3");
		return s; 
	}
	fs_node_t *exists4 = finddir_fs(fs_root, "tmpfile4");
	if (exists4 == NULL) {
		strcat(s, "tmpfile4");
		return s; 
	}
	//uhoh no new ones avaliable!
	return NULL;
}