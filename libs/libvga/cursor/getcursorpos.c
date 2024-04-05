#include <libvga.h>
#include <libports.h>
#include <libssp.h>

unsigned short get_cursor_pos(){
	unsigned short position = 0;

	outb(CURSOR_PORT_COMMAND, 0x0F); // Out port byte 0x0F
	position |= inb(CURSOR_PORT_DATA);

	outb(CURSOR_PORT_COMMAND, 0x0E); // Out port byte 0x0E
	position |= inb(CURSOR_PORT_DATA) << 8; // Combine the two so that they can be factored out easily, but are still 1 number

	return position;
}