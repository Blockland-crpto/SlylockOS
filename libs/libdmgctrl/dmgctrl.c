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
//contains AbridOS code

#include <libvga.h>
#include <drivers/idt.h>
#include <libdmgctrl.h>
#include <libmodule.h>
#include <drivers/nmi.h>
#include <libssp.h>
#include <libdebug.h>
#include <libproc.h>

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
extern void _svi();

void isr_install() {

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
	idt_set_gate(47, (unsigned)_svi, 0x08, 0x8E);
}

//function to initate damage control
void dmgctrl_init() {
	module_t modules_dmgctrl = MODULE("kernel.modules.dmgctrl", "the main error handler for the kernel (CORE)");

	//let the initalization begin!
	INIT(modules_dmgctrl);

	//install isrs
	isr_install();

	//were done!
	DONE(modules_dmgctrl);
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

	
	if (r->int_no < 32)	{

		//lets get the current process
		proc_control_block current_proc = task_queue[0];

		//lets check if the entry is null because if it is we have to panic
		if (current_proc.entry_point == NULL) {
			panic("Kernel triggered a exception", r->int_no);
		} else {
			//a process triggered a exception
			putstr(exception_messages[r->int_no], COLOR_RED, COLOR_BLK);
			putstr(" Exception.\n", COLOR_RED, COLOR_BLK);

			//lets skip to next process
			//lets destory the current process
			proc_destroy(current_proc.id);

			//lets slide down the process pool
			//lets slide it down!
			for (int i = 0; i < 10; i++) {
				task_queue[i] = task_queue[i + 1];
			}

			//now lets recall the schedualer
			proc_scheduler();
		}

	} else if (r->int_no == 48) {
		//oop
		putstr("Spurious vector interrupt", COLOR_RED, COLOR_BLK);
		putstr(" Exception.\n", COLOR_RED, COLOR_BLK);
	}
}