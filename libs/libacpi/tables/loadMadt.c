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
#include <libssp.h>
#include <libmem.h>
#include <libnmi.h>
#include <libpower.h>
#include <libdebug.h>
#include <system/types.h>

//function to get the MADT table
int load_madt(uint32_t* ptr, int entrys) {
	while (0<entrys--) {
		//check if the desired table is reached
		if (acpiCheckHeader((uint32_t *) *ptr, "APIC") == 0) {
			entrys = -2;
			//FIXME: this section is fricken unreadable, that needs to be fixed
			struct MADT *madt = (struct MADT *) *ptr;
			apic_address = madt->local_apic_address;
			apic_flags = madt->flags;
			core_apic_id = madt->lapic_id;
			starting_core_apic_flags = madt->lflags;

			//lets get I/O apic info
			ioapic_addr = madt->io_apic_address;
			gsi_base = madt->global_system_interrupt_base;

			//lets get the interrupt override structure
			//we need to make sure were using the ISA bus
			//because if were not we need to panic
			if (madt->bus == 0x1) {
				//panic!
				panic("invalid bus type reported by ACPI", ACPI_ERROR);
			}

			//lets get the actual global system interrupt and other data
			GLOBAL_SYSTEM_INT = madt->global_system_interrupt;
			MPS_INTI_FLAGS = madt->inti_flags;

			//lets get the non maskable interrupt source info
			nmi_source = madt->nmi_global_system_interrupt;
			return 0;
		}
		ptr++;
	}
	return 1;
}