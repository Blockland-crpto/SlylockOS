#ifndef _GUI_H
#define _GUI_H


//textbox id's
#define TEXTBOX_ID_0 0

//A gui template
void make_gui(int winfg, int winbg, int multipage);

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

#endif 