#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>
#include <cmdset.h>

//the CFA erase sectors command
#define CFA_ERASE_SECTORS 0xC0

//function to erase sectors using CFA
void cfa_erase_sectors(uint32_t LBA, uint8_t sector_count, ata_device_t* dev) {
	//lets first see if CFA is supported
	if(!dev->cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].supported) {
		//oops! cfa erase sectors isn't supported
		//todo: implement a vendor specific CFA handler
		return;
	}

	//next lets see if its enabled
	if(!dev->cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].enabled) {
		//oops! cfa erase sectors isn't enabled
		//todo: find out why
		return;
	}

	//now if wee made it this far, we first need to load the operands into registers
	//we should also see the addressing mode
	if (!dev->lba28_enabled) {
		//function is only supported on LBA28
		return;
	}

	//now lets wait to see if the drive is ready
	wait_ata_drq();
	
	//next lets load the required stuff into registers
	outb(IO_PORT_SECTOR_COUNT, sector_count);
	outb(IO_PORT_SECTOR_NUMBER, (uint8_t) LBA);
	outb(IO_PORT_CYL_LOW, (uint8_t)(LBA >> 8));
	outb(IO_PORT_CYL_HIGH, (uint8_t)(LBA >> 16));
	
	//lets set the drive select
	if (dev->driveType == DRIVE_TYPE_MASTER) {
		//its a master drive
		outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_MASTER);
	} else {
		//its a slave drive
		outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_SLAVE);
	}
	
	//now lets send the command!
	outb(IO_PORT_COMMAND, CFA_ERASE_SECTORS);

	//now lets wait....
	int status = wait_ata_bsy();

	//lets find it
	if (status > 0) {
		//failed
		ata_error_handler();
		return;
	}

	//and were done!
	return;
}