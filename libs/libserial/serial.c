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
#include <libserial.h>
#include <libports.h>
#include <libdebug.h>
#include <libvga.h>
#include <libdmgctrl.h>
#include <kernel/irq.h>
#include <libmodule.h>
#include <libfs.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <libmem.h>

//TODO: add COM2 support and input handling

//serial port handler
void serial_handler(struct regs *r) {
	//ensure were getting OK interrupts
	//lets validate the handler
	if (r->int_no > 256) {
		//got a weird ass interrupt number
		panic("Got a strange interrupt number", INT_ERROR);
	}
}

//serial port writer
void serial_write_char(int8_t data) {
	while(!(inb(COM1 + 5) & 0x20));
	outb(COM1, data);
}

//serial port write string
void serial_write_string(const char* data) {
	for(size_t i = 0; i < strlen(data); i++) {
		serial_write_char(data[i]);
	}
}

//serial port baud setter
void set_serial_baud(uint8_t level) {
	//program the rate into the divisor
	//first lets retrive the current line control value
	uint8_t line_control = inb(COM1_LINE_CTRL);

	//set the significant bit to 1
	line_control |= 0x1;

	//send it back
	outb(COM1_LINE_CTRL, line_control);


	//lets find the least significant bit of divisor
	uint8_t level_lo = level & 0x00000001;
	
	//lets send the least significant bit of the divisor to data
	outb(COM1_DATA, level_lo);

	//lets find the most significant bit of divisor
	uint8_t level_hi = level & (uint8_t)0x10000000;

	//lets send the most significant bit of the divisor to int enable
	outb(COM1_INT_ENABLE, level_hi);

	//now lets reset line control
	line_control = inb(COM1_LINE_CTRL);

	//set most siginificant bit to 0
	line_control |= 0x0;

	//send it back
	outb(COM1_LINE_CTRL, line_control);
}

//serial port initalization function
void serial_init() {
	module_t modules_serial = MODULE("kernel.modules.serial", "Provides serial port support for the kernel");

	//let the initalization begin!
	INIT(modules_serial);
	
	//lets first set the baud rate
	set_serial_baud(BAUD_38400);

	//first lets set data bits
	//lets get the line control register
	uint8_t line_control = inb(COM1_LINE_CTRL);

	//lets set bit zero to 0 and one to 1 to indicate were sending 7 bit chars
	line_control |= 0x00000010;

	//send it back
	outb(COM1_LINE_CTRL, line_control);

	//lets enable interrupt based reception
	outb(COM1_INT_ENABLE, 0x00000001);

	//lets install the irq handler
	irq_install_handler(4, serial_handler);

	//lets enable the serial port
	outb(COM1_MODEM_CTRL, 0x0F);

	//now lets create a file for the terminal
	uint8_t* buffer = (uint8_t*)kalloc(BUFSIZ);
	create_file_fs("com1", buffer, BUFSIZ);

	//were done!
	DONE(modules_serial);
}

