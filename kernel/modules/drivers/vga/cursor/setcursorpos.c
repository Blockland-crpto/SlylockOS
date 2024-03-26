#include <drivers/vga.h>
#include <drivers/io/ports.h>
#include <libssp.h>

void set_cursor_pos(unsigned char x, unsigned char y){
	unsigned short pos = (unsigned short) x + ((unsigned short) VGA_WIDTH * y); // Factors the cursor position together like get_cursor_pos

	if (pos >= VGA_EXTENT){ // If pos >= VGA_EXTENT, set pos to VGA_EXTENT minus 1
		pos = VGA_EXTENT - 1;
	}

	// This just sends a bunch of out port byte commands to set the cursor position
	out_port_byte(CURSOR_PORT_COMMAND, 0x0F);
	out_port_byte(CURSOR_PORT_DATA, (unsigned char) (pos & 0xFF));

	out_port_byte(CURSOR_PORT_COMMAND, 0x0E);
	out_port_byte(CURSOR_PORT_DATA, (unsigned char) ((pos >> 8) & 0xFF));
}