#include <libacpi.h>
#include <system/memory.h>
#include <system/modules.h>
#include <libports.h>
#include <system/types.h>
#include <libvga.h>
#include <system/debug.h>
#include <string.h>
#include <stddef.h>
#include <libssp.h>



int acpiCheckHeader(uint32_t *ptr, char *sig) {
	if (memcmp(ptr, sig, 4) == 0) {
		char *checkPtr = (char *) ptr;
	  	int len = *(ptr + 1);
	  	char check = 0;
	  	while (0<len--) {
		 	check += *checkPtr;
		 	checkPtr++;
	  	}
	  	if (check == 0)
		 	return 0;
   	}
   	return -1;
}

int acpiEnable(void) {
   	// check if acpi is enabled
   	if ( (inw((uint32_t) PM1a_CNT) &SCI_EN) == 0 ) {
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

int initAcpi(void) {
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
						if ( memcmp(S5Addr, "_S5_", 4) == 0)
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

					 		SMI_CMD = facp->SMI_CMD;

					 		ACPI_ENABLE = facp->ACPI_ENABLE;
					 		ACPI_DISABLE = facp->ACPI_DISABLE;

					 		PM1a_CNT = facp->PM1a_CNT_BLK;
					 		PM1b_CNT = facp->PM1b_CNT_BLK;

					 		PM1_CNT_LEN = facp->PM1_CNT_LEN;

					 		SLP_EN = 1<<13;
					 		SCI_EN = 1;

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
	module_t modules_acpi_acpi = MODULE("kernel.modules.acpi.acpi", "Provides ACPI support for the kernel (CORE)");
	INIT(modules_acpi_acpi);
	
	int result = initAcpi();
	
	if (result == 0) {
		DONE(modules_acpi_acpi);
	} else if (result == -1) {
		FAIL(modules_acpi_acpi, "couldn't enable acpi.");
		return;
	} else if (result == -2) {
		FAIL(modules_acpi_acpi, "acpi not avaliable");
		return;
	}
	
	acpiEnable();
	
}