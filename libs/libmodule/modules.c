/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libmodule.h>
#include <libvga.h>
 

module_t MODULE(char* name, char* description) {
	module_t mod;
	mod.usermode = false;
	mod.enabled = true;
	mod.initialized = false;
	mod.name = name;
	mod.description = description;
	return mod;
}

void INIT(module_t module) {
	putstr("[", COLOR_WHT, COLOR_BLK);
	putstr("MODULE",COLOR_DGY, COLOR_BLK);
	putstr("]: Initializing module - ", COLOR_WHT, COLOR_BLK);
	putstr(module.name, COLOR_WHT, COLOR_BLK);
	modules[count] = module;
	if(count == 0) {
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