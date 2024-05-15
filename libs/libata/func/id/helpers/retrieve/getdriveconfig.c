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
 


//function to retrieve config info
void get_drive_config(ata_device_t* drive, uint16_t* identify_data) {
	//compare variable
	uint16_t compare = identify_data[0];
	
	//check if the ATA device is valid
	if ((compare & 0x00) == 1) {
		//the drive is a ATAPI device
		drive->exists = false;
		return;
	}

	//lets reset it
	compare = identify_data[0];
	
	//is the device a ATAPI device?
	if (!drive->atapi_info.is_atapi) {
		//check if the drive is a hard drive
		if ((compare & (1 << 15))) {
			//the drive is a packet device
			drive->exists = false;
			return;
		}
	}

	//lets reset the variable
	compare = identify_data[0];

	//lets see if the drive is removable (its common between ATA and ATAPI devices)
	drive->removable = (compare & (1 << 7)) ? true : false;


	//lets reset it!
	compare = identify_data[0];
	
	//need to check if its a ATAPI device
	//lets see the byte packet information
	if (drive->atapi_info.is_atapi) {
		//lets see the byte packet information
		if ((compare & (1 << 0)) == 1) {
			//the drive has a 16 byte cmd packet
			drive->atapi_info.atapi_cmd_packet_size = ATAPI_CMD_BYTE_16BYTES;
		}

		//lets reset the variable
		compare = identify_data[0];
		
		//lets see if it will set DRQ within recieveing packet command
		if ((compare & (0 << 6)) == 1) {
			//sets within 3 ms of recieving packet command
			drive->atapi_info.atapi_drq_set_times = DRQ_SET_TIMES_3MS;
		} else {
			//send within 50 micro seconds
			drive->atapi_info.atapi_drq_set_times = DRQ_SET_TIMES_50MICROS;
		}
	}

	//return!
	return;
}