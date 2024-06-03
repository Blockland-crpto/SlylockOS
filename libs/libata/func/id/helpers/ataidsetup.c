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
#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//ATA Identify Command
#define IDENTIFY_CMD 0xEC

//helpers
extern int wait_ata_id();
extern void atapi_identify();

//function to setup needed things for ata id
void ata_id_setup(ata_device_t* drive, enum ata_device_select dev) {
	//validate
	if (drive == NULL) {
		//oops!
		return;
	}
	//sets the drive type
	if ((dev & SELECT_DEVICE_MASTER)) {
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
	if ((identify & 0x0) > 0) {
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
		if ((inb(IO_PORT_CYL_LOW) & 0x14)) {
			//the drive is ATAPI, lets just make sure
			if ((inb(IO_PORT_CYL_HIGH) & 0xEB)) {
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