#include <libserial.h>
#include <libports.h>
#include <system/debug.h>
#include <libvga.h>
#include <drivers/isr.h>
#include <drivers/irq.h>
#include <system/modules.h>
#include <libssp.h>
#include <string.h>
#include <system/types.h>
#include <stdarg.h>

//TODO: add COM2 support and input handling

//serial port handler
void serial_handler(struct regs *r) {
	//not used here 
}

//serial port writer
void serial_write_char(int8_t data) {
	while(inb(COM1 + 5) & 0x20 == 0);
	outb(COM1, data);
}

//serial port write string
void serial_write_string(char *data) {
	for(int i = 0; i < strlen(data); i++) {
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
	uint8_t level_hi = level & 0x10000000;

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

	//were done!
	DONE(modules_serial);
}

