#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

#define IDENTIFY_CMD_PI 0xA1

//function to send the identifiy command to ATAPI devices
void atapi_identify(ata_device_t* drive) {
	//send the identify command
	outb(IO_PORT_COMMAND, IDENTIFY_CMD_PI);

	//wait...
	wait_ata_bsy();

	//let retrive id status
	uint8_t identify = inb(IO_PORT_STATUS);

	//now we parse it
	if ((identify & 0x00) == 1) {
		//the drive does not exist
		drive->exists = false;
		return;
	}

	//lets return!
	return;
}