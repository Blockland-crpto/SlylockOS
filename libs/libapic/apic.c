#include <libapic.h>
#include <system/modules.h>
#include <system/types.h>
#include <drivers/cpuid.h>

//static function to check apic (copied from OSdev.org)
static int check_apic(void) {
	unsigned int eax, unused, edx;
	__get_cpuid(1, &eax, &unused, &unused, &edx);
	return edx & CPUID_FEAT_EDX_APIC;
}

// function to initalize the APIC driver
void apic_init() {
	module_t modules_apic_apic = MODULE("kernel.modules.apic.apic", "Provides APIC support for the kernel");

	//let the apic initalization begin!
	INIT(modules_apic_apic);

	//first lets see if a APIC is present
	if (!check_apic()) {
		
		//APIC is not avalible, gota fail!
		FAIL(modules_apic_apic, "APIC is unsupported");
		return;
	}

	//todo: implement apic driver
	
	DONE(modules_apic_apic);
}