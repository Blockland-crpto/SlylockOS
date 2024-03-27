#include <libvga.h>
#include <libports.h>
#include <libssp.h>

void show_cursor(){ // Sends a bunch of out port byte commands to show the cursor
	unsigned char current;

	outb(CURSOR_PORT_COMMAND, 0x0A);
	current = inb(CURSOR_PORT_DATA);
	outb(CURSOR_PORT_DATA, current & 0xC0);

	outb(CURSOR_PORT_COMMAND, 0x0B);
	current = inb(CURSOR_PORT_DATA);
	outb(CURSOR_PORT_DATA, current & 0xE0);
}