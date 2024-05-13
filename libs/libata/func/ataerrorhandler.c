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

//ATA error handler
void ata_error_handler() {
	uint8_t error = inb(IO_PORT_ERROR);
	slog("ATA error occured %d", error);
	if ((error & ERROR_AMNF)) {
		//todo: implement a ata not found error handler
	} else if ((error & ERROR_TKZNF)) {
		//todo: implement a ata track zero not found error handler
	} else if ((error & ERROR_ABRT)) {
		//todo: implement a ata abort error handler
	} else if ((error & ERROR_MCR)) {
		//todo: implement a ata media change request error handler
	} else if ((error & ERROR_IDNF)) {
		//todo: implement a ata id not found error handler
	} else if ((error & ERROR_MC)) {
		//todo: implement a ata media change error handler
	} else if ((error & ERROR_UNC)) {
		//todo: implement a ata uncorrectable error handler
	} else if ((error & ERROR_BBK)) {
		//todo: implement a ata bad block error handler
	}
}