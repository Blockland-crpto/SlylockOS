#include <shell.h>
#include <string.h>
#include <gui.h>
#include <keyboard.h>

void app_info(char *desc, int appid, int box) {
	infobox("App Info:\n", desc, appid, box);
}