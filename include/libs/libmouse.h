#ifndef __LIBMOUSE_H__
#define __LIBMOUSE_H__

#include <system/types.h>

//Mouse commands
enum mouse_commands {
	MOUSE_RESET = 0xFF,
	MOUSE_RESEND = 0xFE,
	MOUSE_SET_DEFAULTS = 0xF6,
	MOUSE_DISABLE_PACKET_STREAMING = 0xF5,
	MOUSE_ENABLE_PACKET_STREAMING = 0xF4,
	MOUSE_SET_SAMPLE_RATE = 0xF3,
	MOUSE_GET_MOUSEID = 0xF2,
	MOUSE_REQ_SINGLE_PACKET = 0xEB,
	MOUSE_STATUS_REQUEST = 0xE9,
	MOUSE_SET_RESOLUTION = 0xE8
};

#if defined(__cplusplus)
extern "C" {
#endif
	//mouse id in int
	int mouse_id;

	//function to wait on mouse
	void mouse_wait(uint8_t a_type);

	//function to write to the mouse
	void mouse_write(uint8_t data);

	//function to read from the mouse
	uint8_t mouse_read();

	//mouse initalization function
	void mouse_install();

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif