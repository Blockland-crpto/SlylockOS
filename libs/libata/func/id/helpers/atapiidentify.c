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