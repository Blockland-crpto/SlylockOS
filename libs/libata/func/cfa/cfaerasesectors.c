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
#include <libacpi.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//the CFA erase sectors command
#define CFA_ERASE_SECTORS 0xC0

//function to erase sectors using CFA
void cfa_erase_sectors(uint32_t LBA, uint8_t sector_count, ata_device_t* dev) {

	//lets first validate the input
	if (LBA == 0 || sector_count == 0 || dev == NULL) {
		return;
	}
	
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
	if (!dev->lba_data.lba28_enabled) {
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

	uint32_t select = SELECT_DEVICE_MASTER;
	uint32_t selects = SELECT_DEVICE_SLAVE;
	select |= (LBA >> 24);
	selects |= (LBA >> 24);
	
	//lets set the drive select
	if (dev->driveType == DRIVE_TYPE_MASTER) {
		//its a master drive
		outb(IO_PORT_DRIVE_HEAD, select);
	} else {
		//its a slave drive
		outb(IO_PORT_DRIVE_HEAD, selects);
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

	//after were done lets check the power mode
	if (PREFERED_PM_PROFILE == 2 || PREFERED_PM_PROFILE == 8) {
		//then we need to put the device in standby mode
		ata_standby();
	}
	
	//and were done!
	return;
}