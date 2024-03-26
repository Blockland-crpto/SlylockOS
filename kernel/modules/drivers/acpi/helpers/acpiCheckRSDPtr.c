#include <drivers/acpi.h>
#include <string.h>
#include <stddef.h>
#include <libssp.h>

unsigned int *acpiCheckRSDPtr(uint32_t *ptr) {
	const char *sig = "RSD PTR ";
	struct RSDPtr *rsdp = (struct RSDPtr *) ptr;


	if (memcmp(sig, rsdp, 8) == 0) {
		unsigned char check = 0;
		if (sizeof(struct RSDPtr) <= sizeof(*ptr)) {
			unsigned char *bptr = (unsigned char *)rsdp;
			for (size_t i = 0; i < 20; i++) {
				check += *bptr;
				bptr++;
			}
		}

		// found valid rsdpd   
		if (check == 0) {
			return (unsigned int *) rsdp->RsdtAddress;
		}
	}

	return NULL;
}