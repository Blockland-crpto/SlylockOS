#include <stdlib.h>
#include <drivers/perip/keybrd.h>

void _Exit(int status) {
	tui_reset();
}