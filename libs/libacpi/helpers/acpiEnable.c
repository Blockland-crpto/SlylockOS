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
#include <libssp.h>


int acpiEnable(void) {
	// check if acpi is enabled
	if ((inw((uint32_t) PM1a_CNT)&SCI_EN) == 0) {
		// check if acpi can be enabled
		if (SMI_CMD != 0 && ACPI_ENABLE != 0) {
			outb((uint32_t) SMI_CMD, ACPI_ENABLE); // send acpi enable command
			// give 3 seconds time to enable acpi
			int i;
			for (i=0; i<300; i++ ) {
				if ( (inw((uint32_t) PM1a_CNT) &SCI_EN) == 1 )
					break;
			}
			if (PM1b_CNT != 0)
				for (; i<300; i++ ) {
					if ( (inw((uint32_t) PM1b_CNT) &SCI_EN) == 1 )
						break;
				}
			if (i<300) {
				//kprintf("enabled acpi.\n");
				acpiEnabled = true;
				return 0;
			} else {
				//kprintf("couldn't enable acpi.\n");
				acpiEnabled = false;
				return -1;
			}
		} else {
			//kprintf("no known way to enable acpi.\n");
			acpiEnabled = false;
			return -2;
		}
	} else {
		//kprintf("acpi was already enabled.\n");
		return 1;
	}
}