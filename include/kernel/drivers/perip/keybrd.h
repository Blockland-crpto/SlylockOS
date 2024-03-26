#ifndef __DRIVERS_PERIP_KEYBRD_H
#define __DRIVERS_PERIP_KEYBRD_H

#define ARROW_KEY_UP '{'
#define ARROW_KEY_DOWN '}'
#define ARROW_KEY_LEFT '<'
#define ARROW_KEY_RIGHT '>'
#define MENU_KEY '?'
#define ENTER_KEY '\n'

#if defined(__cplusplus)
extern "C" {
#endif
	unsigned char ascii_values[128];
	char *inbuf;
	char *buffer;
	char get_key();
	void keyboard_install();
	void track_input(char c);

	void input_reset();
#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif