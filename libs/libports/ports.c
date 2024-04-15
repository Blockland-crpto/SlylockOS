#include <libports.h>
#include <system/types.h>
#include <libssp.h>

unsigned char inb(unsigned short port){
    unsigned char result;
    __asm__ volatile("inb %%dx, %%al": "=a"(result) : "d" (port));

    return result;
}

void outb(unsigned short port, unsigned char data){
	__asm__ volatile("outb %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t inw(uint16_t port) {
 	unsigned char result;
  __asm__ volatile("inw %%dx, %%ax": "=a"(result) : "d" (port));

  return result;
}
void outw(uint16_t port, uint16_t val) {
	asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
}

uint32_t inl(uint16_t port) {
	unsigned char result;
    __asm__ volatile("inl %%edx, %%eax": "=a"(result) : "d" (port));

    return result;
}
void outl(uint16_t port, uint32_t val) {
	asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
}

void io_wait(int iters) {
	for (int i = 0; i < iters; i++) {
		outb(0x80, 0);
	}
}