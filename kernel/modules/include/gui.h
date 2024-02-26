#ifndef __GUI_H
#define __GUI_H


//textbox id's
#define TEXTBOX_ID_0 0

//The GUI init
void gui_init();

//A gui template
void make_gui(int winfg, int winbg, int multipage, int exitopt);

//gui pop up
void make_gui_windows(char *title, char *cont, int beginx, int beginy, int endx, int endy);

//textbox active variable
int textboxactive;

//textbox id
int textboxid;

//text box function
void textbox(char *title, char *cont, int callerid);

//hander for textinput
void textinputhandler(char *input[], int uim);

//loading bar
void loading_bar(int len, int startx, int starty, int delay);

//loading bar two (bouncing bar)
void loading_bar_two(int len, int startx, int starty);

//info box function
void info_box(char *title, char *cont, int callerid, int opts);

//loading screen function
void loadingscreen(char *title, char* desc);

#endif