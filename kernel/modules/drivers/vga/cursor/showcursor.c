#include <drivers/vga.h>
#include <drivers/io/ports.h>

void show_cursor(){ // Sends a bunch of out port byte commands to show the cursor
	unsigned char current;

	out_port_byte(CURSOR_PORT_COMMAND, 0x0A);
	current = in_port_byte(CURSOR_PORT_DATA);
	out_port_byte(CURSOR_PORT_DATA, current & 0xC0);

	out_port_byte(CURSOR_PORT_COMMAND, 0x0B);
	current = in_port_byte(CURSOR_PORT_DATA);
	out_port_byte(CURSOR_PORT_DATA, current & 0xE0);
}