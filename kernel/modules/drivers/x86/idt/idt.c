#include <drivers/x86/idt.h>
#include <system/mod.h>
#include <drivers/vga.h>
#include <system/mem.h>


struct idt_entry {
	unsigned short base_lo;
	unsigned short sel; //this where our kernel segment goes in
	unsigned char always0; //as the name suggests, it is always 0
	unsigned char flags; //these are set using the above table
	unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void load_idt();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
	/* The interrupt routine's base address */
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;

	/* The segment or 'selector' that this IDT entry will use
	*  is set here, along with any access flags */
	idt[num].sel = sel;
	idt[num].always0 = 0;
	idt[num].flags = flags;
}


void idt_install(){
	module_t modules_idt_idt = MODULE("kernel.modules.idt.idt", "IDT for the kernel (CORE)");
	//set the special IDT pointer just like we did in gdt.c
	idtp.limit = (sizeof(struct idt_entry)*256)-1;
	idtp.base = (unsigned int)&idt; //point the base of IDT pointer to our idt_entry's address

	//initialize the IDT with zeros
	//memset(&idt, 0, sizeof(struct idt_entry)*256);

	//tell the processor to point the internal register to the new IDT
	load_idt();
	INIT(modules_idt_idt);
}