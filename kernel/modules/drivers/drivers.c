#include <drivers.h>
#include <memory.h>
#include <modules.h>
#include <ports.h>
#include <types.h>
#include <screen.h>
#include <panic.h>
#include <isr.h>
#include <irq.h>
#include <shell.h>


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
void video_init() {
	module_t modules_video_video = MODULE("kernel.modules.video.video", "Provides video support for the kernel (CORE)");
	if (get_bios_area_video_type() != VIDEO_TYPE_COLOR && get_bios_area_video_type() != VIDEO_TYPE_MONOCHROME) {
		panic("Unable to find screen type", 0x1);
	}
	INIT(modules_video_video);
	
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


/** MMIO DRIVER START **/
uint8_t mmioRead8 (uint64_t p_address) {
	return *((volatile uint8_t*)(p_address));
}
uint16_t mmioRead16 (uint64_t p_address) {
	return *((volatile uint16_t*)(p_address));

}
uint32_t mmioRead32 (uint64_t p_address) {
	return *((volatile uint32_t*)(p_address));

}
uint64_t mmioRead64 (uint64_t p_address) {
	return *((volatile uint64_t*)(p_address));    
}
void mmioWrite8 (uint64_t p_address,uint8_t p_value) {
	(*((volatile uint8_t*)(p_address)))=(p_value);
}
void mmioWrite16 (uint64_t p_address,uint16_t p_value) {
	(*((volatile uint16_t*)(p_address)))=(p_value);    
}
void mmioWrite32 (uint64_t p_address,uint32_t p_value) {
	(*((volatile uint32_t*)(p_address)))=(p_value);
}
void mmioWrite64 (uint64_t p_address,uint64_t p_value) {
	(*((volatile uint64_t*)(p_address)))=(p_value);    
}
/** MMIO DRIVER END **/



/** KEYBOARD DRIVER START **/
#define sizeof(type) (char *)(&type+1)-(char*)(&type)
int enable_shell=0;
char *buffer="";
unsigned char ascii_values[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
	0,	/* Alt */
  ' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	'{',	/* Up Arrow */
	0,	/* Page Up */
  '-',
	'<',	/* Left Arrow */
	0,
	'>',	/* Right Arrow */
  '+',
	0,	/* 79 - End key*/
	'}',	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};
char input_buffer[256];
int i = 0;
void keyboard_handler(struct regs *r){
	unsigned char scancode;

	//Read the Keyboard's data port
	scancode = in_port_byte(0x60);

	if(scancode & 0x80){
		//use Shift, Alt, CTRL keys here
	}
	else{
		char c = ascii_values[scancode];
		if(i==0 && c=='\b'){
		  //do nothing
		  //this prevents clearing the '>' character on the screen
		} else {
		  if (userinputmode > 0 && textboxactive == 0) { 
		  } else if(textboxactive == 1) {
			if (i==0 && c=='\b') {
				//do nothing
				//prevents the backspace from clearing the textbox

			} else if (i >= 33) {
				//do nothing
				//prevents the textbox from overflowing
			} else {
				putchar(c, 8, 7);
			}

		  } else {
			putchar(c, COLOR_WHT, COLOR_BLK);
			//printf("User Prog %d", userinputmode);
		  }
		  track_input(c);
		}
	}

}
char get_key(){
	unsigned char scancode;

	//Read the Keyboard's data port
	scancode = in_port_byte(0x60);
	char *buf;
	kprintf(itoa(scancode, buf, 10));
	if(scancode & 0x80){
		//use Shift, Alt, CTRL keys here
	}
	else{
		char c = ascii_values[scancode];
		return c;
	}
	return 0;

}
void track_input(char c){
		if(userinputmode == 0 && textboxactive == 0) {
		  //If user hits enter, we can execute the command
		  if(c == '\n'){
			//handle shell support here
			//parse_input(input_buffer, i);
			shell(input_buffer, i);
			memset(input_buffer, 0, sizeof(input_buffer));
			i=0;
		  }
		  //handle backspace in input string buffer
		  else if(c == '\b'){
			input_buffer[i-1]='\0';
			i--;
		  }
		  //handle the input buffer if the input is greater than 255
		  else if(i >= 255){
			input_buffer[0]='\0';
			i = 0;
		  }
		  else if(c == '\t') {
		  }
		  //add new input characters from input to string buffer
		  else{
			input_buffer[i]=c;
			i++;
		  }
		} else if(userinputmode > 0 && textboxactive == 0) {
		  //This is a patch to coordinate program responces to key input
		  if (userinputmode == HELP_APP_ID) {
			if (c == '<') {
			  //Do nothing
			} else if (c == '>') {
			  avaliable_commands(2);
			}
		  } else if(userinputmode == HELP_APP_ID_TW) {
			if (c == '<') {
			  avaliable_commands(1);
			} else if (c == '>') {
			  //Do nothing
			}
		  } else if (userinputmode == ABOUT_APP_ID) {
			  if (c == '<') {
				//Do nothing
			  } else if (c == '>') {
				about(2);
			  }
		  } else if (userinputmode == ABOUT_APP_ID_TW) {
			  if (c == '<') {
				about(1);
			  } else if (c == '>') {
				//Do nothing
			  }
		  } else if (userinputmode == LS_APP_ID) {
			  if (c == '<') {
				//Do nothing
			  } else if (c == '>') {
				ls(16, LS_APP_ID_TW, 2);
			  }
		  } else if (userinputmode == LS_APP_ID_TW) {
			  if (c == '<') {
				ls(0, LS_APP_ID, 1);
			  } else if (c == '>') {
				ls(32, LS_APP_ID_TH, 3);
			  }
		  } else if (userinputmode == LS_APP_ID_TH) {
			  if (c == '<') {
				ls(16, LS_APP_ID_TW, 2);
			  } else if (c == '>') {
				ls(48, LS_APP_ID_FR, 4);
			  }
		  } else if (userinputmode == LS_APP_ID_FR) {
			  if (c == '<') {
				ls(32, LS_APP_ID_TH, 3);
			  } else if (c == '>') {
				ls(64, LS_APP_ID_FV, 5);
			  }
		  } else if (userinputmode == LS_APP_ID_FV) {
			  if (c == '<') {
				ls(48, LS_APP_ID_FR, 4);
			  } else if (c == '>') {
				//Do Nothing
			  }
		  }

		  if (c == '\n') {
			clear(COLOR_WHT, COLOR_BLK);
			set_cursor_pos(0,0);
			shell(input_buffer, i);
			memset(input_buffer, 0, sizeof(input_buffer));
			i=0;
			userinputmode = 0;
		  } 
		} else if (textboxactive == 1) {
		 /* 
		 if (i >= 33) {
			  timesfilled + 1;

			  for(int j = 22; j < 56; j++) {
				  putpos('#', 7, 7, j, 15);
			  }
			  set_cursor_pos(22, 15);
			  for(int r = 0; r < 33; r++) {
				  putchar(input_buffer[r + timesfilled], 8, 7);
			  }
			  putchar(c, 8, 7);
			  input_buffer[i] = c;
			  i++;
		  } 
		 */

		  if (c == '\n') {
			clear(COLOR_WHT, COLOR_BLK);
			set_cursor_pos(0,0);
			textboxactive = 0;
			textinputhandler(input_buffer, userinputmode);
			i = 0;
		  } else if(c == '\b'){
			 input_buffer[i-1]='\0';
			 i--;
		  } else {
			input_buffer[i] = c;
			i++;
		  }

		}
}
void keyboard_install(){
	module_t modules_keyboard_keyboard = MODULE("kernel.modules.keyboard.keyboard", "Provides PS/2 keyboard support for the kernel (CORE)");
	char** deps;
	deps[0] = "shell";
	DEPS(modules_keyboard_keyboard, deps);
	irq_install_handler(1, keyboard_handler);
	INIT(modules_keyboard_keyboard);
}
/** KEYBOARD DRIVER END **/