#include <drivers/video.h>
#include <modules.h>
#include <panic.h>
#include <types.h>


uint16_t detect_bios_area_hardware() {
	const uint16_t* bda_detected_hardware_ptr = (const uint16_t*) 0x410;
	return *bda_detected_hardware_ptr;
}

enum video_type get_bios_area_video_type() {
	return (enum video_type) (detect_bios_area_hardware() & 0x30);
}

void video_init() {
	module_t modules_video_video = MODULE("kernel.modules.video.video", "Provides video support for the kernel (CORE)");
	if (get_bios_area_video_type() != VIDEO_TYPE_COLOR && get_bios_area_video_type() != VIDEO_TYPE_MONOCHROME) {
		panic("Unable to find screen type", 0x1);
	}
	INIT(modules_video_video);

}