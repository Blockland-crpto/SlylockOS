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


//get the drives ata version
void get_drive_ata_version(ata_device_t* drive, uint16_t* identify_data) {
	//lets now get the major version supported number
	volatile uint16_t major_version = identify_data[80];
	
	//int representing the major version
	int major_version_int = 3;

	//iterate until we find unsupported
	for (int i = 7; i > 2; i--) {

		//lets now compare
		//i have a variable here because if i don't it will modifiy the actual identfiy data for some reason...
		//lets first copy it
		uint16_t compare = major_version;
		
		//lets check it!
		if ((compare & (1 << i)) == 1) {
			//it is supported
			major_version_int++;
		}
	}
	
	//input it to our drive!
	drive->major_ata_version = major_version_int;

	//lets now get the minor version
	drive->minor_ata_version = identify_data[81];

	//return
	return;
}