#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//CFA translate sector command
#define CFA_TRANSLATE_SECTOR 0x87

//function to get a translated CFA sector
uint8_t* cfa_translate_sector(ata_device_t* dev, uint32_t LBA) {

	//variable for the output
	uint8_t output[512];
	
	//lets first see if CFA is supported
	if(!dev->cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].supported) {
		//oops! cfa feature set isn't supported
		return 0;
	}

	//next lets see if its enabled
	if(!dev->cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].enabled) {
		//oops! cfa feature set isn't enabled
		//todo: find out why
		return 0;
	}

	//set the requied registers
	outb(IO_PORT_SECTOR_NUMBER, (uint8_t) LBA);
	outb(IO_PORT_CYL_LOW, (uint8_t)(LBA >> 8));
	outb(IO_PORT_CYL_HIGH, (uint8_t)(LBA >> 16)); 

	//lets run it!
	//lets first wait till the drive is ready
	wait_ata_drq();

	//next lets send the command
	outb(IO_PORT_COMMAND, CFA_TRANSLATE_SECTOR);

	//and now lets wait for the command to be done
	wait_ata_rdy();

	//now lets iterate
	for (int i = 0; i < 512; i++) {
		//lets get em!
		output[i] = inb(IO_PORT_DATA);
	}

	//lets return it!
	return output;
}