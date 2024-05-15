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
 


//function to retrieve vendor info
void get_drive_vendor(ata_device_t* drive, uint16_t* identify_data) {
	//next lets get the serial number
	for (int i = 10; i < 19; i++) {
		//map it to serial number
		drive->serial_number[i-10] = identify_data[i];
	}

	//next lets get the firmware revision
	for (int i = 23; i < 26; i++) {
		//map it to firmware revision
		drive->firmware_revision[i-23] = identify_data[i];
	}

	//next lets get the model number
	for (int i = 27; i < 46; i++) {
		//map it to model number
		drive->model_number[i-27] = identify_data[i];
	}
}