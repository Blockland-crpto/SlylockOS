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

#ifndef __LIBMOUSE_H__
#define __LIBMOUSE_H__

#include <system/types.h>

//Mouse commands
enum mouse_commands {
	MOUSE_RESET = 0xFF,
	MOUSE_RESEND = 0xFE,
	MOUSE_SET_DEFAULTS = 0xF6,
	MOUSE_DISABLE_PACKET_STREAMING = 0xF5,
	MOUSE_ENABLE_PACKET_STREAMING = 0xF4,
	MOUSE_SET_SAMPLE_RATE = 0xF3,
	MOUSE_GET_MOUSEID = 0xF2,
	MOUSE_REQ_SINGLE_PACKET = 0xEB,
	MOUSE_STATUS_REQUEST = 0xE9,
	MOUSE_SET_RESOLUTION = 0xE8
};

#if defined(__cplusplus)
extern "C" {
#endif
	//mouse id in int
	int mouse_id;

	//function to wait on mouse
	void mouse_wait(uint8_t a_type);

	//function to write to the mouse
	void mouse_write(uint8_t data);

	//function to read from the mouse
	uint8_t mouse_read();

	//mouse initalization function
	void mouse_install();

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif