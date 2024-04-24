//Slylock OS Kernel
#include <system/types.h>

#include <drivers/isr.h>
#include <drivers/irq.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/nmi.h>

#include <libacpi.h>
#include <libapic.h>
#include <libata.h>
#include <libdebug.h>
#include <libfs.h>
#include <libkeyboard.h>
#include <libmultiboot.h>
#include <libmouse.h>
#include <libpci.h>
#include <libports.h>
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
  
  	isr_install();
	
  	irq_install();

	timer_install();
	
	serial_init();
	
	apic_init();
	
  	ata_init();

	nmi_init();

  	pci_init();
	
	acpi_init();
	
	kalloc_init();
		
	rtc_init();
	
	filesystem_init();
	
	keyboard_install();
	
	mouse_install();
	
	vga_init();
	
	libc_init();

	sound_init();

	__asm__ __volatile__("sti");
	
	proc_scheduler();

  	return 0;
}
