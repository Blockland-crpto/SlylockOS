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
#include <libpower.h>
#include <libssp.h>
#include <libproc.h>
#include <libdevmgr.h>
#include <libmodule.h>
#include <string.h>

//function that initates waking
void power_wake(void) {
	//all we need to do is re call the scheduler
	proc_scheduler();
}

//function to initalize power management
void power_init() {
	module_t modules_powermgr = MODULE("kernel.modules.powermgr", "The kernels power manager (CORE)");

	//let the initalization begin!
	INIT(modules_powermgr);

	//we need to get the firmware waking vector
	//we need the address of the function
	void* power_func_addr = &power_wake;

	//now we need to copy the address to the firmware waking vector
	memcpy(FWV, power_func_addr, sizeof(void*));

	//Were done!
	DONE(modules_powermgr);
}