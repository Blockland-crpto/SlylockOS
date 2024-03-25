#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>
#include <drivers/perip/keybrd.h>

void exit(int status) {
	tui_reset();
}