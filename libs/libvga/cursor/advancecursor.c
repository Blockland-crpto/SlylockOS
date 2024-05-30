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
#include <libvga.h>
#include <libports.h>
#include <libdebug.h>
 

void advance_cursor(int mode){
	unsigned short pos = get_cursor_pos(); // Gets the cursor position

	if (mode == 0) {
		pos++; // and increments it by 1
	} else if (mode == 1) {
		pos--; // and decrements it by 1
	} else  {
		panic("advance_cursor: invalid mode", APP_ERROR); // If the mode is invalid, panic
	}

	if (mode == 0) {
		if (pos >= VGA_EXTENT){ // If the positon >= VGA_EXTENT, scroll
			scroll_line();
		}
	}


	// This just sends a bunch of out port byte commands to set the cursor position forward
	outb(CURSOR_PORT_COMMAND, 0x0F);
	outb(CURSOR_PORT_DATA, (unsigned char) (pos & 0xFF));

	outb(CURSOR_PORT_COMMAND, 0x0E);
	outb(CURSOR_PORT_DATA, (unsigned char) ((pos >> 8) & 0xFF));
}