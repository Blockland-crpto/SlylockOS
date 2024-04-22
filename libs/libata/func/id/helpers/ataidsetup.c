#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//ATA Identify Command
#define IDENTIFY_CMD 0xEC

//helpers
extern int wait_ata_id();

//function to setup needed things for ata id
void ata_id_setup(ata_device_t* drive, enum ata_device_select dev) {
	//sets the drive type
	if ((dev & SELECT_DEVICE_MASTER) == 1) {
		drive->driveType = DRIVE_TYPE_MASTER;
	} else {
		drive->driveType = DRIVE_TYPE_SLAVE;
	}

	//selects the drive as master
	outb(IO_PORT_DRIVE_HEAD, dev);

	//sets the required registers to clear
	outb(IO_PORT_SECTOR_COUNT, 0x00);
	outb(IO_PORT_SECTOR_NUMBER, 0x00);
	outb(IO_PORT_CYL_LOW, 0x00);
	outb(IO_PORT_CYL_HIGH, 0x00);

	//sends identify command
	outb(IO_PORT_COMMAND, IDENTIFY_CMD);

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

	//retrive the status of ata waiting
	int status = wait_ata_id();

	//check the status of running the id command
	if (status == 1) {
		//the drive is not a valid ata drive
		drive->exists = false;
		return;
	} else if (status == 2) {
		//the drive errored out while running identify
		drive->exists = false;
		return;
	}

	//if all went well mark the device as existant
	drive->exists = true;
	return;
}