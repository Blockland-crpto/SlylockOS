#ifndef __DRIVERS_PERIP_KEYBRD_H
#define __DRIVERS_PERIP_KEYBRD_H

#define ARROW_KEY_UP '{'
#define ARROW_KEY_DOWN '}'
#define ARROW_KEY_LEFT '<'
#define ARROW_KEY_RIGHT '>'
#define MENU_KEY '?'
#define ENTER_KEY '\n'

unsigned char ascii_values[128];
char *inbuf;
char *buffer;
char get_key();
void keyboard_install();
void track_input(char c);
int userinputmode;
int timesfilled;

void tui_reset();
#endif