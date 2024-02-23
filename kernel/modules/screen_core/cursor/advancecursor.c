#include <screen.h>
#include <ports.h>
#include <panic.h>

void advance_cursor(int mode){
	unsigned short pos = get_cursor_pos(); // Gets the cursor position

	if (mode == 0) {
		pos++; // and increments it by 1
	} else if (mode == 1) {
		pos--; // and decrements it by 1
	} else  {
		panic("advance_cursor: invalid mode", APP_ERROR); // If the mode is invalid, panic
	}

	if (mode == 0) {
		if (pos >= VGA_EXTENT){ // If the positon >= VGA_EXTENT, scroll
			scroll_line();
		}
	}


	// This just sends a bunch of out port byte commands to set the cursor position forward
	out_port_byte(CURSOR_PORT_COMMAND, 0x0F);
	out_port_byte(CURSOR_PORT_DATA, (unsigned char) (pos & 0xFF));

	out_port_byte(CURSOR_PORT_COMMAND, 0x0E);
	out_port_byte(CURSOR_PORT_DATA, (unsigned char) ((pos >> 8) & 0xFF));
}