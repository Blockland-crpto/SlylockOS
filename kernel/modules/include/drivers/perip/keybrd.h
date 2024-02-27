#ifndef __DRIVERS_PERIP_KEYBRD_H
#define __DRIVERS_PERIP_KEYBRD_H



unsigned char ascii_values[128];
char *inbuf;
char *buffer;
char get_key();
void keyboard_install();
void track_input(char c);
int userinputmode;
int timesfilled;

void appinput_handler(char c, int userinputmode);

#endif