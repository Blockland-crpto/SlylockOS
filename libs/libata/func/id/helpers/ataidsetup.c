#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//ATA Identify Command
#define IDENTIFY_CMD 0xEC

//helpers
extern int wait_ata_id();
extern void atapi_identify();

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
	volatile uint8_t identify = inb(IO_PORT_STATUS);

	//now we parse it
	if ((identify & 0x0) == 1) {
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
		//lets check if the drive is ATAPI and act accordingly
		if ((inb(IO_PORT_CYL_LOW) & 0x14) == 1) {
			//the drive is ATAPI, lets just make sure
			if ((inb(IO_PORT_CYL_HIGH) & 0xEB) == 1) {
				//the drive is definatly a ATAPI drive, lets act accordingly
				drive->atapi_info.is_atapi = true;

				//lets first reset the drive. 
				ata_reset();

				//lets get the drive ready
				//selects the drive as master
				outb(IO_PORT_DRIVE_HEAD, dev);

				//sets the required registers to clear
				outb(IO_PORT_SECTOR_COUNT, 0x00);
				outb(IO_PORT_SECTOR_NUMBER, 0x00);
				outb(IO_PORT_CYL_LOW, 0x00);
				outb(IO_PORT_CYL_HIGH, 0x00);
				
				//lets run the atapi id command
				atapi_identify(drive);

				//were done here!
				return;
			}
		} else {
			//the drive is not ATAPI
			drive->exists = false;
			return;
		}
		//todo: add SATA handling
	}

	//if all went well mark the device as existant
	drive->exists = true;
	return;
}