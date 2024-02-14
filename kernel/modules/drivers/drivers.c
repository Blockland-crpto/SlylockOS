#include <drivers.h>
#include <memory.h>
#include <modules.h>
#include <ports.h>
#include <types.h>
#include <screen.h> //temp
#include <panic.h>



/** ATA DRIVER START **/
void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint8_t sector_count) {

	wait_ata_bsy();
	
  out_port_byte(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	
	out_port_byte(0x1F2, sector_count);
	
	out_port_byte(0x1F3, (uint8_t) LBA);
	
	out_port_byte(0x1F4, (uint8_t)(LBA >> 8));
	
	out_port_byte(0x1F5, (uint8_t)(LBA >> 16)); 
	
	out_port_byte(0x1F7,0x20); // Send the read command!
	

	uint16_t *target = (uint16_t*) target_address;
	
	for (int j =0;j<sector_count;j++)
	{
		wait_ata_bsy();
		wait_ata_drq();
		for(int i=0;i<256;i++)
			target[i] = inw(0x1F0);
		target+=256;
	}
	
}
void sect_write_atapio(uint32_t LBA, uint8_t sector_count, uint32_t* bytes) {
	wait_ata_bsy();
	out_port_byte(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	out_port_byte(0x1F2,sector_count);
	out_port_byte(0x1F3, (uint8_t) LBA);
	out_port_byte(0x1F4, (uint8_t)(LBA >> 8));
	out_port_byte(0x1F5, (uint8_t)(LBA >> 16)); 
	out_port_byte(0x1F7,0x30); // Send the write command!

	for (int j =0;j<sector_count;j++)
	{
		wait_ata_bsy();
		wait_ata_drq();
		for(int i=0;i<256;i++)
		{
			outl(0x1F0, bytes[i]);
		}
	}
}
static void wait_ata_bsy() {
	while(in_port_byte(0x1F7)&STATUS_BSY);
}
static void wait_ata_drq() {
	while(!(in_port_byte(0x1F7)&STATUS_RDY));
}
void ata_init() {
	module_t modules_ata_ata = MODULE("kernel.modules.ata.ata", "Provides ATA support for the kernel, read/write (CORE)");
	INIT(modules_ata_ata);
}
/** ATA DRIVER END **/



/** VIDEO DRIVER START **/
uint16_t detect_bios_area_hardware() {
	const uint16_t* bda_detected_hardware_ptr = (const uint16_t*) 0x410;
	return *bda_detected_hardware_ptr;
}
enum video_type get_bios_area_video_type() {
	return (enum video_type) (detect_bios_area_hardware() & 0x30);
}
/** VIDEO DRIVER END **/



/** ACPI DRIVER START **/
unsigned int *acpiCheckRSDPtr(unsigned int *ptr) {
   char *sig = "RSD PTR ";
   struct RSDPtr *rsdp = (struct RSDPtr *) ptr;
   byte *bptr;
   byte check = 0;
   int i;

   if (memcmp(sig, rsdp, 8) == 0)
   {
	  // check checksum rsdpd
	  bptr = (byte *) ptr;
	  for (i=0; i<sizeof(struct RSDPtr); i++)
	  {
		 check += *bptr;
		 bptr++;
	  }

	  // found valid rsdpd   
	  if (check == 0) {
		 /*
		  if (desc->Revision == 0)
			wrstr("acpi 1");
		 else
			wrstr("acpi 2");
		 */
		 return (unsigned int *) rsdp->RsdtAddress;
	  }
   }

   return NULL;
}
unsigned int *acpiGetRSDPtr(void) {
   unsigned int *addr;
   unsigned int *rsdp;

   // search below the 1mb mark for RSDP signature
   for (addr = (unsigned int *) 0x000E0000; (int) addr<0x00100000; addr += 0x10/sizeof(addr))
   {
	  rsdp = acpiCheckRSDPtr(addr);
	  if (rsdp != NULL)
		 return rsdp;
   }


   // at address 0x40:0x0E is the RM segment of the ebda
   int ebda = *((short *) 0x40E);   // get pointer
   ebda = ebda*0x10 &0x000FFFFF;   // transform segment into linear address

   // search Extended BIOS Data Area for the Root System Description Pointer signature
   for (addr = (unsigned int *) ebda; (int) addr<ebda+1024; addr+= 0x10/sizeof(addr))
   {
	  rsdp = acpiCheckRSDPtr(addr);
	  if (rsdp != NULL)
		 return rsdp;
   }

   return NULL;
}
int acpiCheckHeader(unsigned int *ptr, char *sig) {
   if (memcmp(ptr, sig, 4) == 0)
   {
	  char *checkPtr = (char *) ptr;
	  int len = *(ptr + 1);
	  char check = 0;
	  while (0<len--)
	  {
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
   if ( (inw((unsigned int) PM1a_CNT) &SCI_EN) == 0 )
   {
	  // check if acpi can be enabled
	  if (SMI_CMD != 0 && ACPI_ENABLE != 0)
	  {
		 out_port_byte((unsigned int) SMI_CMD, ACPI_ENABLE); // send acpi enable command
		 // give 3 seconds time to enable acpi
		 int i;
		 for (i=0; i<300; i++ )
		 {
			if ( (inw((unsigned int) PM1a_CNT) &SCI_EN) == 1 )
			   break;
		 }
		 if (PM1b_CNT != 0)
			for (; i<300; i++ )
			{
			   if ( (inw((unsigned int) PM1b_CNT) &SCI_EN) == 1 )
				  break;
			}
		 if (i<300) {
			kprintf("enabled acpi.\n");
		    acpiEnabled = 1;
			return 0;
		 } else {
			kprintf("couldn't enable acpi.\n");
			acpiEnabled = 2;
			return -1;
		 }
	  } else {
		 kprintf("no known way to enable acpi.\n");
		 acpiEnabled = 0;
		 return -1;
	  }
   } else {
	  //wrstr("acpi was already enabled.\n");
	  return 0;
   }
}
int initAcpi(void) {
   unsigned int *ptr = acpiGetRSDPtr();

   // check if address is correct  ( if acpi is available on this pc )
   if (ptr != NULL && acpiCheckHeader(ptr, "RSDT") == 0)
   {
	  // the RSDT contains an unknown number of pointers to acpi tables
	  int entrys = *(ptr + 1);
	  entrys = (entrys-36) /4;
	  ptr += 36/4;   // skip header information

	  while (0<entrys--)
	  {
		 // check if the desired table is reached
		 if (acpiCheckHeader((unsigned int *) *ptr, "FACP") == 0)
		 {
			entrys = -2;
			struct FACP *facp = (struct FACP *) *ptr;
			if (acpiCheckHeader((unsigned int *) facp->DSDT, "DSDT") == 0)
			{
			   // search the \_S5 package in the DSDT
			   char *S5Addr = (char *) facp->DSDT +36; // skip header
			   int dsdtLength = *(facp->DSDT+1) -36;
			   while (0 < dsdtLength--)
			   {
				  if ( memcmp(S5Addr, "_S5_", 4) == 0)
					 break;
				  S5Addr++;
			   }
			   // check if \_S5 was found
			   if (dsdtLength > 0)
			   {
				  // check for valid AML structure
				  if ( ( *(S5Addr-1) == 0x08 || ( *(S5Addr-2) == 0x08 && *(S5Addr-1) == '\\') ) && *(S5Addr+4) == 0x12 )
				  {
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
					 kprintf("\\_S5 parse error.\n");
				  }
			   } else {
				   kprintf("\\_S5 not present.\n");
			   }
			} else {
				kprintf("DSDT invalid.\n");
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
void acpiPowerOff(void) {
   // SCI_EN is set to 1 if acpi shutdown is possible
   if (SCI_EN == 0)
	  return;

   acpiEnable();

   // send the shutdown command
   outw((unsigned int) PM1a_CNT, SLP_TYPa | SLP_EN );
   if ( PM1b_CNT != 0 )
	  outw((unsigned int) PM1b_CNT, SLP_TYPb | SLP_EN );

   kprintf("acpi poweroff failed.\n");
}
void acpi_init() {
	module_t modules_acpi_acpi = MODULE("kernel.modules.acpi.acpi", "Provides ACPI support for the kernel (CORE)");
	initAcpi();
	acpiEnable();
	INIT(modules_acpi_acpi);
}
/** ACPI DRIVER END **/



/** PCI DRIVER START **/
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	uint32_t address;
	uint32_t lbus  = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	uint16_t tmp = 0;

	// Create configuration address as per Figure 1
	address = (uint32_t)((lbus << 16) | (lslot << 11) |
			  (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

	// Write out the address
	outl(0xCF8, address);
	// Read in the data
	// (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
	tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
	return tmp;
}
uint16_t pciCheckVendor(uint8_t bus, uint8_t slot) {
	uint16_t vendor, device;
	/* Try and read the first configuration register. Since there are no
	 * vendors that == 0xFFFF, it must be a non-existent device. */
	if ((vendor = pciConfigReadWord(bus, slot, 0, 0)) != 0xFFFF) {
	   device = pciConfigReadWord(bus, slot, 0, 2);
	} return (vendor);
}
/** PCI DRVIER END **/