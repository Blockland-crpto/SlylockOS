#include <libsound.h>
#include <libssp.h>
#include <libports.h>
#include <libmodule.h>
#include <libmem.h>
#include <system/types.h>
#include <drivers/isr.h>
#include <drivers/irq.h>

//sound handler function
void sound_handler(struct regs* r) {
	//todo
}

//dsp reset function
void dsp_reset(sound_device_t* dev) {
	//lets send 1 to dsp reset port 
	outb(AUDIO_DSP_PORT_RESET, 0x1);

	//lets wait (were suppose to wait 3 micro seconds)
	io_wait(3);

	//next send 0 to dsp reset port
	outb(AUDIO_DSP_PORT_RESET, 0x0);

	//lets see if DSP read port returned 0xAA
	//the dsp read port value
	uint8_t dsp_read = inb(AUDIO_DSP_PORT_READ);

	//lets compare that to 0xAA
	if (dsp_read & 0xAA) {
		//it worked!
		return;
	} else if (dsp_read & 0x00) {
		//the card does not exist
		dev->exists = false;
		return;
	} else {
		//it returned the DSP version
		dev->version = dsp_read;
		return;
	}
}

//DMA programming function 
void dma_program_8bit(uint8_t data) {
	//first lets disable the DMA channel
	outb(AUDIO_DMA_CHANNEL_PORT, 0x05);

	//lets set the flip flop to 1
	outb(AUDIO_DMA_CHANNEL_FLIP_FLOP_PORT, 0x01);

	//next lets set the transfer mode
	outb(AUDIO_DMA_CHANNEL_TRANSFER_MODE, 0x49); // set to single mode

	//lets get the address
	uintptr_t data_address = (uintptr_t)data;
	
	//lets get the page
	uintptr_t page = (data_address >> 6) & 0x03;

	//lets get the address hi
	uintptr_t addr_hi = (data_address >> 2) & 0x03;

	//lets get the address lo
	uintptr_t addr_lo = data_address & 0x03;

	//now lets send the page to the DMA channel
	outb(AUDIO_DMA_PAGE_PORT, page);

	//now lets send the addr hi to the DMA channel
	outb(AUDIO_DMA_CHANNEL_ADDRESS_PORT, addr_hi);

	//now lets send the addr lo to the DMA channel
	outb(AUDIO_DMA_CHANNEL_ADDRESS_PORT, addr_lo);

	//lets wait
	io_wait(1);

	//now lets get the data size
	size_t size = sizeof(data);

	//lets get the size hi
	uint8_t size_hi = (size >> 4) & 0x03;

	//lets get the size lo
	uint8_t size_lo = size & 0x03;
	
	//send high
	outb(AUDIO_DMA_CHANNEL_COUNT_PORT, size_hi);

	//send low
	outb(AUDIO_DMA_CHANNEL_COUNT_PORT, size_lo);

	//lets wait
	io_wait(1);

	//now lets enable the channel!
	outb(AUDIO_DMA_CHANNEL_PORT, 0x01);
}

//sound initalization function
void sound_init() {
	module_t modules_sound = MODULE("kernel.modules.sound", "Provides sound support for the kernel");

	//let the sound init begin!
	INIT(modules_sound);

	//our sound device
	sound_device_t sound_device;

	//next lets reset its dsp
	dsp_reset(&sound_device);

	//lets see if it exists
	if (sound_device.exists == false) {
		//failed as it does not exist
		FAIL(modules_sound, "Sound device does not exist");
	}
	
	//lets get the DSP version
	outb(AUDIO_DSP_PORT_WRITE, AUDIO_DSP_WRITE_CMD_GET_DSP_VERSION);

	//now lets wait
	io_wait(3);

	//now lets get it
	uint8_t dsp_version = inb(AUDIO_DSP_PORT_READ);

	//and at it to our sound object
	sound_device.version = dsp_version;

	//now lets set its irq
	outb(AUDIO_DSP_PORT_MIXER, AUDIO_MIXER_CMD_SET_IRQ);

	//it will be irq 5 for simplicity
	outb(AUDIO_DSP_PORT_MIXER, 0x02);
	
	//lets install the handler
	irq_install_handler(5, sound_handler);

	//awesome!
	
	//its done
	DONE(modules_sound);
}