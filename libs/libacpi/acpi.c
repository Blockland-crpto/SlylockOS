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


//helper
extern int acpiCheckHeader();
extern int acpiEnable();



int load_acpi(void) {
   	uint32_t *ptr = acpiGetRSDPtr();

   	// check if address is correct  ( if acpi is available on this pc )
   	if (ptr != NULL && acpiCheckHeader(ptr, "RSDT") == 0) {
	  	// the RSDT contains an unknown number of pointers to acpi tables
	  	int entrys = *(ptr + 1);
	  	entrys = (entrys-36) /4;
	 	ptr += 36/4;   // skip header information

	  	while (0<entrys--) {
		 	// check if the desired table is reached
		 	if (acpiCheckHeader((uint32_t *) *ptr, "FACP") == 0) {
				entrys = -2;
				struct FACP *facp = (struct FACP *) *ptr;
				if (acpiCheckHeader((uint32_t *) facp->DSDT, "DSDT") == 0) {
			   		// search the \_S5 package in the DSDT
			   		char *S5Addr = (char *) facp->DSDT +36; // skip header
			   		int dsdtLength = *(facp->DSDT+1) -36;
				
			   		while (0 < dsdtLength--) {
						if (memcmp(S5Addr, "_S5_", 4) == 0)
					 		break;
				  		S5Addr++;
			   		}
				
			   		// check if \_S5 was found
			   		if (dsdtLength > 0) {
				  		// check for valid AML structure
				  		if ( ( *(S5Addr-1) == 0x08 || ( *(S5Addr-2) == 0x08 && *(S5Addr-1) == '\\') ) && *(S5Addr+4) == 0x12 ) {
					 		S5Addr += 5;
					 		S5Addr += ((*S5Addr &0xC0)>>6) +2;   // calculate PkgLength size

					 		if (*S5Addr == 0x0A)
								S5Addr++;   // skip byteprefix
					 		SLP_TYPa = *(S5Addr)<<10;
					 		S5Addr++;

					 		if (*S5Addr == 0x0A)
								S5Addr++;   // skip byteprefix
					 		SLP_TYPb = *(S5Addr)<<10;

							PREFERED_PM_PROFILE = facp->Preferred_PM_Profile;
							SCI_INT = facp->SCI_INT;
					 		SMI_CMD = facp->SMI_CMD;
					 		ACPI_ENABLE = facp->ACPI_ENABLE;
					 		ACPI_DISABLE = facp->ACPI_DISABLE;
							S4BIOS_REQ = facp->S4BIOS_REQ;
							PSTATE_CNT = facp->PSTATE_CNT;
							PM1a_EVT = facp->PM1a_EVT_BLK;
							PM1b_EVT = facp->PM1b_EVT_BLK;
					 		PM1a_CNT = facp->PM1a_CNT_BLK;
					 		PM1b_CNT = facp->PM1b_CNT_BLK;
							PM2_CNT = facp->PM2_CNT_BLK;
							PM_TMR = facp->PM_TMR_BLK;
							GPE0 = facp->GPE0_BLK;
							GPE1 = facp->GPE1_BLK;
							PM1_EVT_LEN = facp->PM1_EVT_LEN;
					 		PM1_CNT_LEN = facp->PM1_CNT_LEN;
							PM2_CNT_LEN = facp->PM2_CNT_LEN;
							PM_TMR_LEN = facp->PM_TMR_LEN;
							GPE0_LEN = facp->GPE0_BLK_LEN;
							GPE1_LEN = facp->GPE1_BLK_LEN;
							GPE1_BASE = facp->GPE1_BASE;
							
							

							

					 		SLP_EN = 1<<13;
					 		SCI_EN = 1;

							//slog("PM profile %d", (int)PREFERED_PM_PROFILE);

					 		return 0;
				  		} else {
					 		//unable to parse S5
					 		panic("_S5 parse error.", ACPI_ERROR);
				  		}
			   		} else {
				   		//S5 is not present
				   		panic("_S5 not present.", ACPI_ERROR);
			   		}
				} else {
					panic("DSDT parse error.", ACPI_ERROR);
				}
			}
		 	ptr++;
	  	}
	   	panic("acpi table not found.\n", ACPI_ERROR);
   	} else {
		kprintf("no acpi.\n");
   	}
   	return -1;
}

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