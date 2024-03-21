#include <drivers/cpu/cpuid.h>
#include <system/mod.h>


static inline int cpuid_string(int code, int where[4]) {
  __asm__ volatile ("cpuid":"=a"(*where),"=b"(*(where+0)), "=d"(*(where+1)),"=c"(*(where+2)):"a"(code));
  return (int)where[0];
}

const char * const cpu_string() {
	static char s[16] = "BogusProces!";
	cpuid_string(0, (int*)(s));
	return s;
}

void cpuid_init() {
	module_t modules_cpuid_cpuid = MODULE("kernel.modules.cpuid.cpuid", "identifies the Processor");
	INIT(modules_cpuid_cpuid);
	 
	
}