#include <drivers/fs/fs.h>
#include <system/mltb/multiboot.h>
#include <system/panic.h>
#include <system/types.h>
#include <system/mltb/multibootinfo.h>
#include <system/exec.h>
#include <system/usermode.h>
#include <system/im.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <drivers/x86/isr.h>
#include <drivers/x86/irq.h>
#include <drivers/io/ports.h>
#include <drivers/x86/gdt.h>
#include <drivers/x86/idt.h>
#include <drivers/cpu/nmi.h>
#include <drivers/io/ata.h>
#include <drivers/vga.h>
#include <drivers/acpi.h>
#include <drivers/perip/pci.h>
#include <drivers/cpu/cpuid.h>
#include <drivers/perip/timer.h>

#define MB_MAGIC 0x1BADB002

int main(multiboot_info_t* mb_info, uint32_t magic){
  mbi = mb_info;
  set_cursor_pos(0,0);
  clear(COLOR_WHT, COLOR_BLK);
  kprintf("---loading kernel\n\\->");
  putstr("done.\n", COLOR_GRN, COLOR_BLK);
  kprintf("---checking grub's memory map\n\\->");
  if(!(mb_info->flags >> 6 & 0x1)) {
	  	putstr("fail.\n", COLOR_RED, COLOR_BLK);
        panic("invalid memory map given by GRUB bootloader", MEMORY_MAP_INVALID);
  } 
  putstr("done.\n", COLOR_GRN, COLOR_BLK);
  //install and initialize everything
  /*
   * ORDER (- = line, > = arrow right, , = arrow down, ^ = arrow up, . means bottom to left (or bottom to right), X means end of trace):
   * gdt-X
   * idt --------->irq-----------,
   *       \-isr----^          timer------->shell--->keyboard-X
   *              \--------------^          .-^
   * initrd-------------------->fs---------/
   *
   * ata-X
   *
   * memory-X
   *
   * libc-X
   */    
  
  //execute_program("./test");
  
  

  gdt_install();
  idt_install();
  ata_init();

  isr_install();
  irq_install();
  nmi_init();
	
  timer_install();
  filesystem_init();

  shell_init();
  
  keyboard_install();
  malloc_init();
  vga_init();

  libc_init();
  acpi_init();
  gui_init();
  
  
  pci_init();
  cpuid_init();
  loadingscreen("Starting Up", "MiniOS is starting...");
  im_init();
	
  __asm__ __volatile__("sti");


  
  // print the welcome message
  //putstr("Welcome to ", COLOR_GRY, COLOR_BLK);
  //putstr("MiniOS\n", COLOR_CYN, COLOR_BLK);

  //textbox("test", "test"); 
	
  //kprintf(">");
  return 0;
}
