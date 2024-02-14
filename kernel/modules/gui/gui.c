#include <gui.h>
#include <screen.h>
#include <keyboard.h>
#include <shell.h>
#include <modules.h>


void gui_init() {
	module_t modules_gui_gui = MODULE("kernel.modules.gui.gui", "GUI for the kernel (CORE)");
	INIT(modules_gui_gui);
}

void make_gui_windows(char *title, char *cont, int beginx, int beginy, int endx, int endy) {
  for(int y = beginy; y < endy; y++) {
	for(int x = beginx; x < endx; x++) {
	  putpos("#", 7, 7, x, y);
	}
  }

  for(int x = beginx; x < endx; x++) {
	putpos("#", 8, 7, x, endy);
	putpos("#", 8, 7, x, beginy);
  }
  for(int y = beginy; y < endy+1; y++) 
  {
	putpos("#", 8, 7, beginx, y);
	putpos("#", 8, 7, endx, y);
  }
  putstrpos(title, beginx+1, beginy+1, 8, 7, beginx+1);
  putstrpos(cont, beginx+1, beginy+3, 8, 7, beginx+1);
  return 0;
}

void make_gui(int winfg, int winbg, int multipage) {
  for(int y = 0; y<2; y++) {
	for(int x = 0; x<80; x++) {
	  putpos("#", 7, 7, x, y);
	}
  }
  for(int y = 25; y > 1; y--) {
	for(int x = 0; x<80; x++) {
	  putpos("#", winfg, winbg, x, y);
	}
  }

  for (int i = 0; i < multipage; i++) {
	  putpos("=", 8, 7, 49 + i, 1);
  }
  return 0;
}

void textbox(char *title, char *cont, int callerid) {

	textboxactive = 1;
	userinputmode = callerid;
	make_gui(3, 3, 0);
	make_gui_windows(title, "", 19, 10, 60, 20);
	for (int x = 21; x < 58; x++) {
		putpos('#', 8, 7, x, 14);
		putpos('#', 8, 7, x, 16);
	}

	for (int y = 14; y < 16; y++) {
		putpos('#', 8, 7, 21, y);
		putpos('#', 8, 7, 57, y);
	}

	set_cursor_pos(22, 15);
}

void textinputhandler(char *input[], int uim) {
	//printf("%s", input);
	if (uim == CAT_APP_ID) {
		cat(input);
	}
}

void bootscreen() {
	make_gui(3, 3, 0);
	make_gui_windows("Starting Up", "MiniOS is starting...", 19, 10, 60, 20);
	//gives a chance for the modules to initialize
	for(int i = 0; i < 10000000; i++) {
		__asm__ __volatile__("sti");
	}
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
}
