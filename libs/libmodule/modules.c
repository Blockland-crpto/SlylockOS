#include <libmodule.h>
#include <libvga.h>
#include <libssp.h>


#define NULL 0

module_t MODULE(char* name, char* description) {
	module_t mod;
	mod.usermode = false;
	mod.enabled = true;
	mod.initialized = false;
	mod.name = name;
	mod.description = description;
	return mod;
}

int INIT(module_t module) {
	putstr("[", COLOR_WHT, COLOR_BLK);
	putstr("MODULE",COLOR_DGY, COLOR_BLK);
	putstr("]: Initializing module - ", COLOR_WHT, COLOR_BLK);
	putstr(module.name, COLOR_WHT, COLOR_BLK);
	modules[count] = module;
	if(count == NULL) {
		count = 1;
	} else {
		count++;
	}	
}

void FAIL(module_t module, char* reason) {
	putstr(" [", COLOR_WHT, COLOR_BLK);
	putstr("FAILED",COLOR_RED, COLOR_BLK);
	putstr("] - ", COLOR_WHT, COLOR_BLK);
	putstr(reason, COLOR_WHT, COLOR_BLK);
	kprintf("\n");
	module.initialized = false;
}

void DONE(module_t module) {
	putstr(" [", COLOR_WHT, COLOR_BLK);
	putstr("SUCCESS", COLOR_GRN, COLOR_BLK);
	putstr("]\n", COLOR_WHT, COLOR_BLK);
	module.initialized = true;
}

void DISABLE(module_t module) {
	module.enabled = false;
}
void ENABLE(module_t module) {
	module.enabled = true;
}
void DEPS(module_t module, char** dependencies) {
	module.dependencies = dependencies;
}