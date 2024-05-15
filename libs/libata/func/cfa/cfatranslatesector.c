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
#include <system/types.h>
 
#include <stddef.h>

//CFA translate sector command
#define CFA_TRANSLATE_SECTOR 0x87

//function to get a translated CFA sector
uint8_t* cfa_translate_sector(ata_device_t* dev, uint32_t LBA) {

	//input validation
	if (dev == NULL || LBA == NULL) {
		//oops!
		return 0;
	}
	
	//variable for the output
	static uint8_t output[512];
	
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
	wait_ata_bsy();

	//now lets iterate
	for (int i = 0; i < 512; i++) {
		//lets get em!
		output[i] = inb(IO_PORT_DATA);
	}

	//after were done lets check the power mode
	if (PREFERED_PM_PROFILE == 2 || PREFERED_PM_PROFILE == 8) {
		//then we need to put the device in standby mode
		ata_standby();
	}
	
	//lets return it!
	return output;
}