#include <drivers/vga.h>
#include <drivers/io/ports.h>

void hide_cursor(){ // Sends a couple out port byte commands to hide the cursor
	out_port_byte(CURSOR_PORT_COMMAND, 0x0A);
	out_port_byte(CURSOR_PORT_DATA, 0x20);
}