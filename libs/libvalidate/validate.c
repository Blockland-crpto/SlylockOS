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
#include <libvalidate.h>
#include <libmodule.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <libproc.h>

//function to initate the validation system
void validate_init() {
	module_t modules_validater = MODULE("kernel.modules.validater", "The kernels validation system (CORE)");

	//let the initalization begin!
	INIT(modules_validater);


	//were done!
	DONE(modules_validater);
}

//function to validate input
bool valid_check_char(char* test, const char** valid, size_t validlen, size_t arraylen) {
	//lets check if the input fits the requirements
	if (test == NULL || valid == NULL || validlen == 0 || arraylen == 0) {
		return false;
	}

	//lets see if test is a valid length
	if (strlen(test) > validlen) {
		return false;
	}

	// lets see if it meets the requirements for validity
	for (size_t i = 0; i < arraylen; i++) {
		if (strcmp(test, valid[i]) == 0) {
			return true;
		}
	}

	//if it doesn't work
	return false;
}

//function to validate a memory block is free
bool valid_mem_check(void* test, size_t len) {
	uint8_t* s = (uint8_t*)test;
	//lets iterate through the memory 
	for (size_t i = 0; i < len; i++) {
		if (s[i] != '0') {
			return false;
		}
	}
	return true;
}