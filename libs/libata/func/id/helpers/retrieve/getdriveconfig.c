#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>


//function to retrieve config info
void get_drive_config(ata_device_t* drive, uint16_t drive_config) {
	//lets have the drive type mask
	uint16_t drivetype_mask = 1 << 15;

	//lets have the removable drive mask
	uint16_t removable_mask = 1 << 7;

	//check if the ATA device is valid
	if (drive_config&0x00) {
		//the drive is not existent
		drive->exists = false;
		return;
	}

	//check if the drive is a hard drive
	if (drive_config&drivetype_mask) {
		//the drive is a packet device
		drive->exists = false;
		return;
	}

	//lets see if the drive is removable
	if (drive_config&removable_mask) {
		//the drive is removable
		drive->removable = true;
	} else {
		//the drive is not removable
		drive->removable = false;
	}
	
	return;
}