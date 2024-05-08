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

//Poll ATA till the status is 7
int wait_ata_id() {
	while((inb(CTRL_ALTERNATE_STATUS) & STATUS_BSY) == 1) {
		if ((inb(IO_PORT_CYL_LOW) & 0x00) == 1) {
			//Not a valid ATA drive
			return 1;
		}
		if ((inb(IO_PORT_CYL_HIGH) & 0x00) == 1) {
			//Not a valid ATA drive
			return 1;
		}
	}
	if((inb(IO_PORT_STATUS) & STATUS_DRQ) == 1) {
		return 3;
	} else if ((inb(IO_PORT_STATUS) & STATUS_ERR) == 1) {
		return 2;
	}
	return 0;
}