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

//function to get the drive cmd set 2
void get_drive_cmd_set_2(ata_device_t* drive, uint16_t* identify_data) {

	//input validate
	if (drive == NULL || identify_data == NULL) {
		//oops!
		return;
	}
	
	//for loop to iterate through the word
	for (int i = 13; i >= 0; i--) {

		//lets reset the variable
		uint16_t command_sets2 = identify_data[83];
		
		//supported bool
		bool supported = (command_sets2 & (1 << i)) ? true : false;

		//switched the mask
		switch(i) {
			case 13: {
				//is the FLUSH CACHE EXT command supported
				drive->cmd_set_supported[FLUSH_CACHE_EXT_SUPPORTED].supported = supported;
				break;
			}
			case 12: {
				//is the mandatory FLUSH CACHE command supported
				drive->cmd_set_supported[MANDATORY_FLUSH_CACHE_SUPPORTED].supported = supported;
				break;
			}
			case 11: {
				//is the device configuration overlay feature set supported
				drive->cmd_set_supported[DEVICE_CONFIG_OVERLAY_SUPPORTED].supported = supported;
				break;
			}
			case 10: {
				//is the 48 bit address feature set supported
				drive->cmd_set_supported[LBA48_ENABLED].supported = supported;
				break;
			}
			case 9: {
				//is automatic acoustic management supported
				drive->cmd_set_supported[AUTO_ACOUSTIC_MANAGEMENT_SUPPORTED].supported = supported;
				break;
			}
			case 8: {
				//is SET MAX security extentsion supported
				drive->cmd_set_supported[SET_MAX_SECURITY_EXTENTSION_SUPPORTED].supported = supported;
				break;
			}
			case 6: {
				//is drive spin up required for set features after power up?
				drive->set_features_spinup_needed = supported;
				break;
			}
			case 5: {
				//is power up in standby supported
				drive->cmd_set_supported[POWER_UP_IN_STANDBY_SUPPORTED].supported = supported;
				break;
			}
			case 4: {
				//is removable media status notification supported
				drive->cmd_set_supported[REMOVEABLE_MEDIA_STATUS_SUPPORTED].supported = supported;
				break;
			}
			case 3: {
				//is the advanced power management set supported
				drive->cmd_set_supported[ADVANCED_POWER_MANAGEMENT_SUPPORTED].supported = supported;
				break;
			}
			case 2: {
				//is the CFA feature set supported
				drive->cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 1: {
				//is READ/WRITE DMA QUEUED command supported
				drive->cmd_set_supported[READ_WRITE_DMA_QUEUED_SUPPORTED].supported = supported;
				break;
			}
			case 0: {
				//is DOWNLOAD MICROCODE command supported
				drive->cmd_set_supported[DOWNLOAD_MICROCODE_SUPPORTED].supported = supported;
				break;
			}
			default: {
				//nothing
				break;
			}
		}
	}
}