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
#include <libdevmgr.h>
#include <libdebug.h>
#include <libmodule.h>
#include <libmouse.h>
#include <libmem.h>
#include <libacpi.h>
#include <system/types.h>

//function to initalize the device manager
void devmgr_init() {
	module_t modules_kernel_devmgr = MODULE("kernel.modules.devmgr", "The kernel device manager (CORE)");

	//let the initalization begin!
	INIT(modules_kernel_devmgr);

	//we need acpi for this to work
	if (!acpiEnabled) {
		//oops no ACPI!
		FAIL(modules_kernel_devmgr, "ACPI is not enabled");
		return;
	}
	
	//gotta parse the IA_BOOT_ARCH
	boot_cfg = ia_boot_parser();

	//lets create a stream for the mouse
	mouse_stream = (mouse_packet_t*)kalloc(256);

	//lets check if the kalloc returned valid
	if (mouse_stream == NULL) {
		//oops no memory!
		panic("No more memory!", INSUFFICIENT_RAM);
	}
	
	//were done!
	DONE(modules_kernel_devmgr);
}


//function to authorize a device usage
bool devmgr_authorize_device(enum device_type dev) {
	//lets see if the device is supported
	switch(dev) {
		case DEVICE_TYPE_ISA: {
			//return if its supported
			return boot_cfg.isa_supported;
		}
		case DEVICE_TYPE_8042: {
			//check if 8042 controller is supported
			return boot_cfg.ctrler_8042_supported;
		}
		case DEVICE_TYPE_VGA: {
			//check if vga is supported
			return boot_cfg.vga_present;
		}
		case DEVICE_TYPE_MSI: {
			//check if MSI is supported
			return !boot_cfg.msi_unsupported;
		}
		case DEVICE_TYPE_PCI: {
			//check if PCIE controls are supported
			return boot_cfg.pcie_ctrls_supported;
		}
		case DEVICE_TYPE_CMOS: {
			//check if CMOS is supported
			return !boot_cfg.cmos_not_present;
		}
		default: {
			//why you trying to ask us a unknown question!?
			panic("invalid devmgr request", DEVMGR_ERROR);
		}
	}
	//we should not be here....
	panic("internal devmgr error", DEVMGR_ERROR);
	
	//return to get the compiler to shutup
	return false;
}