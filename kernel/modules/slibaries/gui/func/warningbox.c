#include <drivers/vga.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <slibaries/shell.h>

void warning_box(char *title, char *cont) {
	userinputmode = WARN_BOX_ID;
	infobox(title, cont, WARN_BOX_ID, 0);
}