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
#include <system/types.h>
#include <libmodule.h>
#include <libssp.h>

//Resets ATA
void ata_reset() {
	//todo: use device reset command to reset if able to
	//lets check if the ATA supports device reset
	if (!ata_drives[0].cmd_set_supported[DEVICE_RESET_SUPPORTED].supported) {
		//no support
		return;
	}
	outb(CTRL_DEVICE, DEV_CTRL_SRST);
	outb(CTRL_DEVICE, 0x00);
	outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_SLAVE);
	outb(CTRL_DEVICE, 0x00);
	outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_MASTER);
	return;
}