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
#ifndef __LIBSERIAL_H__
#define __LIBSERIAL_H__

#include <stdint.h>
#include <stdbool.h>

//serial ports
enum serial_ports {
	COM1 = 0x3F8,
	COM2 = 0x2F8
};

//serial port registers
enum com_1_serial_port_registers {
	COM1_DATA = COM1+0,
	COM1_INT_ENABLE = COM1+1,
	COM1_INT_ID_FIFO_CTRL = COM1+2,
	COM1_LINE_CTRL = COM1+3,
	COM1_MODEM_CTRL = COM1+4,
	COM1_LINE_STATUS = COM1+5,
	COM1_MODEM_STATUS = COM1+6,
	COM1_SCRATCH = COM1+7
};

enum com_2_serial_port_registers {
	COM2_DATA = COM2+0,
	COM2_INT_ENABLE = COM2+1,
	COM2_INT_ID_FIFO_CTRL = COM2+2,
	COM2_LINE_CTRL = COM2+3,
	COM2_MODEM_CTRL = COM2+4,
	COM2_LINE_STATUS = COM2+5,
	COM2_MODEM_STATUS = COM2+6,
	COM2_SCRATCH = COM2+7
};

//diffrent baud rates
enum baud_rates {
	BAUD_115200 = 0x0000001,
	BAUD_57600 = 0x0000002,
	BAUD_38400 = 0x0000003,
};

#if defined(__cplusplus)
extern "C" {
#endif
	
	//serial initalization function
	void serial_init();

	//serial baud setter
	void set_serial_baud(uint8_t level);

	//serial port writer
	void serial_write_string(const char *data);

	//serial port write char
	void serial_write_char(int8_t data);
#if defined(__cplusplus)
} /* extern "C" */
#endif
	
#endif