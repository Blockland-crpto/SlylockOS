#ifndef __LIBSERIAL_H__
#define __LIBSERIAL_H__

#include <system/types.h>

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
	void serial_write_string(char *data);
	
#if defined(__cplusplus)
} /* extern "C" */
#endif
	
#endif