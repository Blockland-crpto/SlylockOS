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
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//function to get the drive cmd set 1
void get_drive_cmd_set_1(ata_device_t* drive, uint16_t* identify_data) {

	//lets input validate!
	if (drive == NULL || identify_data == NULL) {
		//oops!
		return;
	}
	
	//for loop to iterate through the word
	for (int i = 14; i >= 0; i--) {

		//lets reset the variable
		uint16_t command_sets1 = identify_data[82];

		//switched the mask
		switch(i) {
			case 14: {
				//is the nop command supported
				drive->cmd_set_supported[NOP_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 13: {
				//is the read buffer command supported
				drive->cmd_set_supported[READ_BUFFER_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 12: {
				//is the write buffer command supported
				drive->cmd_set_supported[WRITE_BUFFER_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 11: {
				//this is not used
				continue;
			}
			case 10: {
				//is the host protected area supported
				drive->cmd_set_supported[HOST_PROTECTED_AREA_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 9: {
				//is the reset command supported
				drive->cmd_set_supported[DEVICE_RESET_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 8: {
				//is service interrupt is supported
				drive->cmd_set_supported[SERVICE_INTERRUPT_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 7: {
				//is release interrupt supported
				drive->cmd_set_supported[RELEASE_INTERRUPT_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 6: {
				//is look ahead supported
				drive->cmd_set_supported[LOOK_AHEAD_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 5: {
				//is the write cache command supported
				drive->cmd_set_supported[WRITE_CACHE_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 4: {
				//is the packet command supported
				drive->cmd_set_supported[PACKET_COMMAND_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 3: {
				//is the power management set supported
				drive->cmd_set_supported[POWER_MANAGEMENT_SET_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 2: {
				//is the removable device set supported
				drive->cmd_set_supported[REMOVABLE_DEVICE_SET_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 1: {
				//is the security mode feature set supported
				drive->cmd_set_supported[SECURITY_MODE_FEATURE_SET_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			case 0: {
				//is SMART feature set supported
				drive->cmd_set_supported[SMART_FEATURE_SET_SUPPORTED].supported = enabled(i, command_sets1);
				break;
			}
			default: {
				//not anything
				break;
			}
		}
	}
}