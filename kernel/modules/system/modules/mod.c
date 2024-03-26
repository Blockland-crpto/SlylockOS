#include <system/mod.h>
#include <drivers/vga.h>
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
	kprintf("Initializing module - ");
	kprintf(module.name);
	modules[count] = module;
	if(count == NULL) {
		count = 1;
	} else {
		count++;
	}
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