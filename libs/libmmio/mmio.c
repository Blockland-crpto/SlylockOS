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
#include <libmmio.h>
#include <system/types.h>
 

uint8_t mmioRead8 (uint32_t* p_address) {
	return *p_address;
}

uint16_t mmioRead16 (uint32_t* p_address) {
	return *p_address;
}

uint32_t mmioRead32 (uint32_t* p_address) {
	return *p_address;
}

//todo: ensure its not a null pointer to prevent undefined behavior
void mmioWrite8 (uint32_t* p_address, uint8_t p_value) {
	*p_address=p_value;
}

void mmioWrite16 (uint32_t* p_address,uint16_t p_value) {
	*p_address=p_value;    
}

void mmioWrite32 (uint32_t* p_address,uint32_t p_value) {
	*p_address=p_value;
}
