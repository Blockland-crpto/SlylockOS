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
#include <libacpi.h>
#include <libmem.h>
#include <libmodule.h>
#include <libports.h>
#include <system/types.h>
#include <libvga.h>
#include <libdebug.h>
#include <string.h>
#include <stddef.h>
 


//helper
extern int acpiCheckHeader();
extern int acpiEnable();


void acpi_init() {
	module_t modules_acpi = MODULE("kernel.modules.acpi", "Provides ACPI support for the kernel (CORE)");
	INIT(modules_acpi);
	
	int result = load_acpi();
	
	if (result == 0) {
		DONE(modules_acpi);
	} else if (result == -1) {
		FAIL(modules_acpi, "couldn't enable acpi.");
		return;
	} else if (result == -2) {
		FAIL(modules_acpi, "acpi not avaliable");
		return;
	}
	
	acpiEnable();

}