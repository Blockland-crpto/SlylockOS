#include <drivers/vga.h>
#include <libssp.h>

enum video_type get_bios_area_video_type() {
	return (enum video_type) (detect_bios_area_hardware() & 0x30);
}