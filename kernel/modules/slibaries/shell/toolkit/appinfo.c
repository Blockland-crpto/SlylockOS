#include <slibaries/shell.h>
#include <string.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>

void app_info(char *desc, int appid, int box) {
	infobox("App Info:\n", desc, appid, box);
}