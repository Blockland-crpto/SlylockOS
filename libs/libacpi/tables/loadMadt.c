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
#include <libnmi.h>
#include <libpower.h>
#include <libdebug.h>
#include <libdevmgr.h>
#include <system/types.h>

//function to get the MADT table
int load_madt(uint32_t* ptr, int entrys) {
	while (0<entrys--) {
		//check if the desired table is reached
		if (acpiCheckHeader((uint32_t *) *ptr, "APIC") == 0) {
			entrys = -2;
			//FIXME: this section is fricken unreadable, that needs to be fixed
			struct MADT *madt = (struct MADT *) *ptr;

			//lets get the local apic address
			apic_address = madt->local_apic_address;
			apic_flags = madt->flags;

			//lets increment the MADT from over the header
			ptr = (uint32_t *) *ptr;
			ptr += sizeof(struct MADT);

			
			//for loop it
			for (;;) {
				//now lets get the local apic
				struct MADT_LAPIC *lapic = (struct MADT_LAPIC *) *ptr;

				//lets parse it	
				cpu.cores[cpu.core_count].corenum = cpu.core_count;
				cpu.cores[cpu.core_count].enabled = false;
				cpu.cores[cpu.core_count].acpi_uid = lapic->acpi_processor_uid;
				cpu.cores[cpu.core_count].lapic_id = lapic->apic_id;
				cpu.cores[cpu.core_count].lapic_flags = lapic->flags;

				//increment core count
				cpu.core_count++;

				//next lets see if the next one is a local apic
				ptr = (uint32_t *) *ptr;
				ptr += sizeof(struct MADT_LAPIC);

				//lets check the header
				struct acpi_subheader *sub = (struct acpi_subheader *) *ptr;

				//lets check if its a local apic
				if (sub->type != 0) {
					//its not local apic
					break;
				}
			}

			ptr = (uint32_t *) *ptr;
			
			//same thing with IO apic
			for (;;) {
				//now lets get the io apic
				struct MADT_IOAPIC *ioapic = (struct MADT_IOAPIC *) *ptr;

				//lets parse it
				cpu.ioapics[cpu.io_apic_count].io_apic_id = ioapic->io_apic_id;
				cpu.ioapics[cpu.io_apic_count].io_apic_address = ioapic->io_apic_address;
				cpu.ioapics[cpu.io_apic_count].global_system_interrupt_base = ioapic->global_system_interrupt_base;
				
				//increment the ioapic count
				cpu.io_apic_count++;
				
				//lets move to the next entry
				ptr = (uint32_t *) *ptr;
				ptr += sizeof(struct MADT_IOAPIC);

				//lets check the header
				struct acpi_subheader *sub = (struct acpi_subheader *) *ptr;

				//lets check if its a io apic
				if (sub->type != 1) {
					//its not io apic
					break;
				}
			}

			return 0;
		}
		ptr++;
	}
	return 1;
}