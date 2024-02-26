#include <drivers/vga.h>
#include <drivers/io/ports.h>

unsigned short get_cursor_pos(){
	unsigned short position = 0;

	out_port_byte(CURSOR_PORT_COMMAND, 0x0F); // Out port byte 0x0F
	position |= in_port_byte(CURSOR_PORT_DATA);

	out_port_byte(CURSOR_PORT_COMMAND, 0x0E); // Out port byte 0x0E
	position |= in_port_byte(CURSOR_PORT_DATA) << 8; // Combine the two so that they can be factored out easily, but are still 1 number

	return position;
}
