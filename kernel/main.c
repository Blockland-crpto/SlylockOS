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
//Slylock OS Kernel

#include <system/types.h>

#include <drivers/irq.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/nmi.h>

#include <libacpi.h>
#include <libapic.h>
#include <libata.h>
#include <libdebug.h>
#include <libdelegate.h>
#include <libdevmgr.h>
#include <libdmgctrl.h>
#include <libfs.h>
#include <libkeyboard.h>
#include <libmultiboot.h>
#include <libmouse.h>
#include <libpci.h>
#include <libpic.h>
#include <libports.h>
#include <libpower.h>
#include <libproc.h>
#include <librtc.h>
#include <libserial.h>
#include <libsound.h>
#include <libsse.h>
#include <libssp.h>
#include <libtimer.h>
#include <libvga.h>

#define MB_MAGIC 0x1BADB002

__attribute__ ((constructor)) void init_kernel() {
	set_cursor_pos(0,0);
	clear(COLOR_WHT, COLOR_BLK);
	return;
}

int main(multiboot_info_t* mb_info, uint32_t magic){
	mbi = mb_info;

	// check the grub memory map
	if(!(mb_info->flags >> 6 & 0x1)) {
		// if its invalid
		panic("invalid memory map given by GRUB bootloader", MEMORY_MAP_INVALID);
	} 

	sse_init();
	
  	gdt_install();
	
  	idt_install();
  
  	dmgctrl_init();
	
  	irq_install();

	acpi_init();

	pic_init();
	
	apic_init();

	power_init();
	
	devmgr_init();
	
	timer_install();

	serial_init();
	
  	ata_init();

	nmi_init();

  	pci_init();
	
	kalloc_init();
		
	rtc_init();
	
	filesystem_init();
	
	keyboard_install();
	
	mouse_install();
	
	vga_init();
	
	libc_init();

	sound_init();

	delegate_init();

	__asm__ __volatile__("sti");

	proc_scheduler();

  	return 0;
}
