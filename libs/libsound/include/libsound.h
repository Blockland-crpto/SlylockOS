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
#ifndef __LIBSOUND_H
#define __LIBSOUND_H

#include <system/types.h>

//audio port addresses
enum audio_dsp_ports {
	AUDIO_DSP_PORT_MIXER = 0x224,
	AUDIO_DSP_PORT_DATA = 0x225,
	AUDIO_DSP_PORT_RESET = 0x226,
	AUDIO_DSP_PORT_READ = 0x22A,
	AUDIO_DSP_PORT_WRITE = 0x22C,
	AUDIO_DSP_PORT_STATUS = 0x22E,
	AUDIO_DSP_PORT_INT_ACK = 0x22F, // acknowledge 16 bit interrupts
};

//dsp write commands
enum audio_dsp_write_cmds {
	AUDIO_DSP_WRITE_CMD_SET_TIME_CONSTANT = 0x40,
	AUDIO_DSP_WRITE_CMD_SET_OUTPUT_SAMPLE_RATE = 0x41,
	AUDIO_DSP_WRITE_CMD_TURN_SPEAKER_ON = 0xD1,
	AUDIO_DSP_WRITE_CMD_TURN_SPEAKER_OFF = 0xD3,
	AUDIO_DSP_WRITE_CMD_STOP_8BIT_CHANNEL = 0xD0,
	AUDIO_DSP_WRITE_CMD_RESUME_8BIT_CHANNEL = 0xD4,
	AUDIO_DSP_WRITE_CMD_STOP_16BIT_CHANNEL = 0xD5,
	AUDIO_DSP_WRITE_CMD_RESUME_16BIT_CHANNEL = 0xD6,
	AUDIO_DSP_WRITE_CMD_GET_DSP_VERSION = 0xE1,
};

//mixer port commands
enum audio_mixer_cmds {
	AUDIO_MIXER_CMD_MASTER_VOLUME = 0x22,
	AUDIO_MIXER_CMD_SET_IRQ = 0x80,
};

//DMA channel control port
enum audio_dma_channel_ports {
	AUDIO_DMA_CHANNEL_PORT = 0x0A,
	AUDIO_DMA_CHANNEL_TRANSFER_MODE = 0x0B,
	AUDIO_DMA_CHANNEL_FLIP_FLOP_PORT = 0x0C,
	AUDIO_DMA_PAGE_PORT = 0x83,
	AUDIO_DMA_CHANNEL_ADDRESS_PORT = 0x02,
	AUDIO_DMA_CHANNEL_COUNT_PORT = 0x03,
};

#if defined(__cplusplus)
extern "C" {
#endif

	//a Sound device object
	typedef struct {

		//it exists right?
		bool exists;

		//do we have its version?
		uint8_t version;
	
	} sound_device_t;
	
	//the initalization function
	void sound_init();

	//the DMA programming function
	void dma_program_8bit(uint8_t data);
	
	//the dsp reset function
	void dsp_reset(sound_device_t* dev);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif 