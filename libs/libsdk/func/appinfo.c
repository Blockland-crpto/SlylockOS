#include <shell/shell.h>
#include <libsdk.h>
#include <libtui.h>

void app_info(char *desc, int appid, int box) {
	infobox("App Info:\n", desc, appid, box);
}