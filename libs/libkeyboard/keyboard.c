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
#include <libvga.h>
#include <libdmgctrl.h>
#include <drivers/irq.h>
#include <libkeyboard.h>
#include <libmodule.h>
#include <libssp.h>
#include <string.h>
#include <libmem.h>
#include <libdebug.h>

#define sizeof(type) (char *)(&type+1)-(char*)(&type)

char *buffer="";

unsigned char ascii_values[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	'?',			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
	0,	/* Alt */
  ' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	'{',	/* Up Arrow */
	0,	/* Page Up */
  '-',
	'<',	/* Left Arrow */
	0,
	'>',	/* Right Arrow */
  '+',
	0,	/* 79 - End key*/
	'}',	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

char input_buffer[256];

int i = 0;

void keyboard_handler(struct regs *r){
	unsigned char scancode;
	if (r->int_no > 256) {
		//got a weird ass interrupt number
		panic("Got a strange interrupt number", INT_ERROR);
	}
	
	//Read the Keyboard's data port
	scancode = inb(0x60);

	if(scancode & 0x80){
		//use Shift, Alt, CTRL keys here
	}
	else{
		char c = ascii_values[scancode];
		if(i==0 && c=='\b'){
		  //do nothing
		  //this prevents clearing the '>' character on the screen
		} else {
			kputchar(c, COLOR_WHT, COLOR_BLK);
		 	track_input(c);
		}
	}

}

char get_key(){
	unsigned char scancode;

	//Read the Keyboard's data port
	scancode = inb(0x60);
	char *buf = (char*)kalloc(sizeof(scancode));
	kprintf((const char*)itoa(scancode, buf, 10));
	if((scancode & 0x80)) {
		//use Shift, Alt, CTRL keys here
	} else{
		char c = ascii_values[scancode];
		//lets free it
		kfree(buf);
		return c;
	}

	kfree(buf);
	return 0;
}

void track_input(const char c){
	kprintc(c);
	return;
}

void input_reset() {
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
	//shell(input_buffer, i);
	memset(input_buffer, 0, sizeof(input_buffer));
	i=0;
}

void keyboard_install(){
	module_t modules_keyboard = MODULE("kernel.modules.keyboard", "Provides PS/2 keyboard support for the kernel (CORE)");
	INIT(modules_keyboard);
	irq_install_handler(1, keyboard_handler);
	DONE(modules_keyboard);
	 
}