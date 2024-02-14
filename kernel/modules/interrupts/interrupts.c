#include <screen.h>
#include <memory.h>
#include <interrupts.h>
#include <modules.h>
#include <ports.h>


/** INTERRUPT DESCRIPTOR TABLE START **/
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
	nmi_enable();
	INIT(modules_idt_idt);
}
/** INTERRUPT DESCRIPTOR TABLE END **/


/** NON MASKABLE INTERRUPT START **/
void nmi_enable() {
	out_port_byte(0x70, in_port_byte(0x70) & 0x7F);
	in_port_byte(0x71);
}
void nmi_disable() {
	out_port_byte(0x70, in_port_byte(0x70) | 0x80);
	in_port_byte(0x71);
}
/** NON MASKABLE INTERRUPT END **/


/** INTERRUPT SERVICE ROUTINES START **/
extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();
void isr_install() {
	module_t modules_isr_isr = MODULE("kernel.modules.isr.isr", "Provides ISR support for the kernel (CORE)");
	char** deps;
	deps[0] = "kernel.modules.idt.idt";
	DEPS(modules_isr_isr, deps);
	idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned)_isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned)_isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned)_isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)_isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)_isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned)_isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)_isr7, 0x08, 0x8E);

	idt_set_gate(8, (unsigned)_isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)_isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)_isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)_isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)_isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)_isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)_isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)_isr15, 0x08, 0x8E);

	idt_set_gate(16, (unsigned)_isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)_isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)_isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)_isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)_isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)_isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)_isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)_isr23, 0x08, 0x8E);

	idt_set_gate(24, (unsigned)_isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)_isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)_isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)_isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)_isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)_isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned)_isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned)_isr31, 0x08, 0x8E);
	INIT(modules_isr_isr);
}
char *exception_messages[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",

	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",

	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",

	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};
void fault_handler(struct regs *r) {
	if (r->int_no < 32)
	{
		putstr(exception_messages[r->int_no], COLOR_RED, COLOR_BLK);
		putstr(" Exception.\n", COLOR_RED, COLOR_BLK);
		for(;;);
	}
}
/** INTERRUPT SERVICE ROUTINES END **/


/** INTERRUPT REQUEST START **/
extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();
void *irq_routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};
void irq_install_handler(int irq, void(*handler)(struct regs *r)){
	irq_routines[irq] = handler;
}
void irq_uninstall_handler(int irq){
	irq_routines[irq] = 0;
}
void irq_remap(void){
	out_port_byte(0x20, 0x11);
	out_port_byte(0xA0, 0x11);
	out_port_byte(0x21, 0x20);
	out_port_byte(0xA1, 0x28);
	out_port_byte(0x21, 0x04);
	out_port_byte(0xA1, 0x02);
	out_port_byte(0x21, 0x01);
	out_port_byte(0xA1, 0x01);
	out_port_byte(0x21, 0x0);
	out_port_byte(0xA1, 0x0);
}
void irq_install(){
	module_t modules_irq_irq = MODULE("kernel.modules.irq.irq", "Provides IRQ support for the kernel (CORE)");
	char** deps;
	deps[0] = "kernel.modules.idt.idt";
	deps[1] = "kernel.modules.isr.isr";
	DEPS(modules_irq_irq, deps);
	irq_remap();

	//mapping the IRQs to 32-47 IDT entries
	idt_set_gate(32, (unsigned)_irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)_irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)_irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)_irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)_irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)_irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)_irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)_irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)_irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)_irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)_irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)_irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)_irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)_irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)_irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)_irq15, 0x08, 0x8E);
	INIT(modules_irq_irq);
}
void irq_handler(struct regs *r){

	//blank function pointer
	void (*handler)(struct regs *r);

	//check whether we have a custom handler to run the IRQ and execute it
	handler = irq_routines[r->int_no - 32];

	if(handler){
		handler(r);
	}

	//if the IDT entry is greater than 40, then it is second PIC (IRQ8 to IRQ15)
	//then we need to send EOI to Slave or second PIC
	if(r->int_no >= 40){
		out_port_byte(0xA0, 0x20);
	}

	//in other cases,we do the following
	out_port_byte(0x20, 0x20);

}
/** INTERRUPT SERVICE ROUTINES END **/