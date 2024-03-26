#include <drivers/vga.h>
#include <system/types.h>
#include <libssp.h>

uint16_t detect_bios_area_hardware() {
	const uint16_t* bda_detected_hardware_ptr = (const uint16_t*) 0x410;
	return *bda_detected_hardware_ptr;
}