#include <drivers/vga.h>
#include <drivers/io/ports.h>
#include <libssp.h>

void hide_cursor(){ // Sends a couple out port byte commands to hide the cursor
	outb(CURSOR_PORT_COMMAND, 0x0A);
	outb(CURSOR_PORT_DATA, 0x20);
}