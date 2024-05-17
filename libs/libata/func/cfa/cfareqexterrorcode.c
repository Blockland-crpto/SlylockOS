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

//CFA error code command
#define CFA_REQ_EXT_ERROR_CODE 0x03

//function to get a extended CFA error code
uint8_t cfa_req_ext_error_code(ata_device_t* dev) {
	//input validation!
	if (dev == NULL) {
		return 0;
	}
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
	wait_ata_bsy();

	//lets get the data
	uint8_t data = inb(IO_PORT_ERROR);

	//after were done lets check the power mode
	if (PREFERED_PM_PROFILE == 2 || PREFERED_PM_PROFILE == 8) {
		//then we need to put the device in standby mode
		ata_standby();
	}

	//lets return it!
	return data;
}