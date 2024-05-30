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
#include <libapic.h>
#include <libmem.h>
#include <libmodule.h>
#include <libports.h>
#include <libpower.h>
#include <libdevmgr.h>
#include <stdint.h>
#include <stdbool.h>
#include <libvga.h>
#include <libdebug.h>
#include <string.h>
#include <stddef.h>
 

//helpers
extern int load_fadt();
extern int load_madt();

int load_acpi(void) {
	uint32_t *ptr = acpiGetRSDPtr();

	// check if address is correct  ( if acpi is available on this pc )
	if (ptr != NULL && acpiCheckHeader(ptr, "RSDT") == 0) {

		//table results
		int fadt_found;
		int madt_found;
		
		//lets loop through the tables
		for (int i = 0; i < 2; i++) {
			ptr = acpiGetRSDPtr();
			
			// the RSDT contains an unknown number of pointers to acpi tables
			int entrys = *(ptr + 1);
			entrys = (entrys-36) /4;
			ptr += 36/4;   // skip header information
			
			//switch through
			switch(i) {
				case 1: {
					madt_found = load_madt(ptr, entrys);
					break;
				}
				case 0: {
					fadt_found = load_fadt(ptr, entrys);
					break;
				}
			}
		}
		
		//lets check if its okay
		if (fadt_found == 0 && madt_found == 0) {
			//were okay!
			return 0;
		} else {
			panic("acpi table not found.\n", ACPI_ERROR);
		}
		
	} else {
		kprintf("no acpi.\n");
	}
	return -1;
}

//function to parse the IA boot flags parser
ia_boot_arch_t ia_boot_parser() {

	//our future return value
	ia_boot_arch_t ret;

	//get the boot flags
	int16_t boot_flags = IAPC_BOOT_ARCH;

	//variable used as buffer to compare
	int16_t compare;

	//iterate over the boot flags
	for (int i = 0; i < 6; i++) {
		//lets compare
		compare = boot_flags & (1 << i);

		//switch!
		switch (i) {
			case 0: {
				ret.isa_supported = (compare & (1 << i)) ? true : false;
				break;
			}
			case 1: {
				ret.ctrler_8042_supported = (compare & (1 << i)) ? true : false;
				break;
			}
			case 2: {
				ret.vga_present = (compare & (0 << i)) ? true : false;
				break;
			}
			case 3: {
				ret.msi_unsupported = (compare & (1 << i)) ? true : false;
				break;
			}
			case 4: {
				ret.pcie_ctrls_supported = (compare & (1 << i)) ? true : false;
				break;
			}
			case 5: {
				ret.cmos_not_present = (compare & (1 << i)) ? true : false;
				break;
			}
			default: {
				//shouldn't do this...
				break;
			}
		}
	}
	return ret;
}