//Slylock OS Kernel
#include <system/multiboot/multiboot.h>
#include <system/multiboot/multibootinfo.h>

#include <system/debug.h>
#include <system/types.h>

#include <drivers/isr.h>
#include <drivers/irq.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/nmi.h>

#include <libvga.h>
#include <libacpi.h>
#include <libata.h>
#include <libports.h>
#include <libfs.h>
#include <libmouse.h>
#include <libserial.h>
#include <libpci.h>
#include <libtimer.h>
#include <librtc.h>
#include <libkeyboard.h>
#include <libapic.h>
#include <libssp.h>
#include <libsound.h>

#define MB_MAGIC 0x1BADB002

__attribute__ ((constructor)) void init_kernel() {
	stack_chk_init();
	return;
}

int main(multiboot_info_t* mb_info, uint32_t magic){
  	mbi = mb_info;
  	set_cursor_pos(0,0);
  	clear(COLOR_WHT, COLOR_BLK);
	// check the grub memory map
	if(!(mb_info->flags >> 6 & 0x1)) {
	  	// if its invalid
    	panic("invalid memory map given by GRUB bootloader", MEMORY_MAP_INVALID);
  	} 

	
  	gdt_install();
	
  	idt_install();
  
  	isr_install();
	
  	irq_install();
	
	apic_init();
	
  	ata_init();

	nmi_init();
	
  	pci_init();
	
	acpi_init();
	
	kalloc_init();
	
	timer_install();
	
	rtc_init();
	
	filesystem_init();
	
	keyboard_install();
	
	mouse_install();
	
	vga_init();
	
	libc_init();

	serial_init();

	sound_init();
	
	kprintf("Hello World!");
  	__asm__ __volatile__("sti");

  	return 0;
}
