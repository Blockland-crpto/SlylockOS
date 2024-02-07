#include <usermode.h>

#include <modules.h>

void usermode_init() {
	module_t modules_usermode_usermode = MODULE("kernel.modules.usermode.usermode", "Allows switching to user mode in the kernel.");
   // Set up a stack structure for switching to user mode.
   asm volatile("  \
     cli; \
     mov $0x23, %ax; \
     mov %ax, %ds; \
     mov %ax, %es; \
     mov %ax, %fs; \
     mov %ax, %gs; \
                   \
     mov %esp, %eax; \
     pushl $0x23; \
     pushl %eax; \
     pushf; \
     pushl $0x1B; \
     push $1f; \
     iret; \
   1: \
     ");
	 INIT(modules_usermode_usermode);
} 