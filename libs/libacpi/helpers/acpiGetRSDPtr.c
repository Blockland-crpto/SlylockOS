#include <libacpi.h>
#include <system/types.h>
#include <stddef.h>
#include <libssp.h>

unsigned int *acpiGetRSDPtr(void) {
   	unsigned int *addr;
   	unsigned int *rsdp;

   	// search below the 1mb mark for RSDP signature
   	for (addr = (uint32_t *) 0x000E0000; (int) addr<0x00100000; addr += 0x10/sizeof(addr)) {
	  	rsdp = acpiCheckRSDPtr(addr);
	  	if (rsdp != NULL)
		 	return rsdp;
   	}


   	// at address 0x40:0x0E is the RM segment of the ebda
   	int ebda = *((short *) 0x40E);   // get pointer
   	ebda = ebda*0x10 &0x000FFFFF;   // transform segment into linear address

	// search Extended BIOS Data Area for the Root System Description Pointer signature
   	for (addr = (uint32_t *) ebda; (int) addr<ebda+1024; addr+= 0x10/sizeof(addr)) {
	  	rsdp = acpiCheckRSDPtr(addr);
	  	if (rsdp != NULL)
		 	return rsdp;
   	}

   	return NULL;
}