#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>
#include <cmdset.h>

#define CFA_REQ_EXT_ERROR_CODE 0x03

//function to get a extended CFA error code
uint8_t cfa_req_ext_error_code(ata_device_t* dev) {
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

	//lets first wait till the drive is ready
	wait_ata_drq();

	//next lets send the command
	outb(IO_PORT_COMMAND, CFA_REQ_EXT_ERROR_CODE);

	//and now lets wait for the command to be done
	wait_ata_rdy();

	//lets get the data
	uint8_t data = inb(IO_PORT_ERROR);

	//lets return it!
	return data;
}