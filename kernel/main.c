//Slylock OS Kernel
#include <system/mltb/multiboot.h>
#include <system/mltb/multibootinfo.h>

#include <system/debug.h>
#include <system/types.h>

#include <shell/shell.h>

#include <drivers/vga.h>
#include <drivers/acpi.h>

#include <drivers/x86/isr.h>
#include <drivers/x86/irq.h>
#include <drivers/x86/gdt.h>
#include <drivers/x86/idt.h>

#include <drivers/io/ata.h>
#include <drivers/io/ports.h>

#include <drivers/fs/fs.h>


#include <drivers/cpu/nmi.h>
#include <drivers/cpu/cpuid.h>

#include <drivers/perip/pci.h>
#include <drivers/perip/timer.h>
#include <drivers/perip/rtc.h>
#include <drivers/perip/keybrd.h>

#include <libssp.h>

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
  	ata_init();

	nmi_init();
	
  	cpuid_init();
  	pci_init();
	acpi_init();
	kalloc_init();
	
	timer_install();
	rtc_init();
	filesystem_init();
	keyboard_install();
	shell_init();
	
	vga_init();
	libc_init();

	kprintf("Hello World!");
  	__asm__ __volatile__("sti");

  	return 0;
}
