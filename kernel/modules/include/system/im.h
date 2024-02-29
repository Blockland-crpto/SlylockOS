#ifndef __SYSTEM_IM_H
#define __SYSTEM_IM_H

//slim

#define SLIM_VERSION "1.0.0"

void appinput_handler(char c, int userinputmode);

void helpim(char c, int userinputmode);
void aboutim(char c, int userinputmode);
void lsim(char c, int userinputmode);
void catim(char c, int userinputmode);
void calcim(char c, int userinputmode);
void shellim(char c, int userinputmode);
void powerim(char c, int userinputmode);
void homeim(char c, int userinputmode);

void im_init();

#endif