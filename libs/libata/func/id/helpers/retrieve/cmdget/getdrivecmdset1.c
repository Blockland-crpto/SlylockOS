#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//function to get the drive cmd set 1
void get_drive_cmd_set_1(ata_device_t* drive, uint16_t* identify_data) {

	//for loop to iterate through the word
	for (int i = 14; i >= 0; i--) {

		//lets reset the variable
		uint16_t command_sets1 = identify_data[82];
		
		//supported bool
		bool supported = (command_sets1 & (1 << i)) ? true : false;

		//switched the mask
		switch(i) {
			case 14: {
				//is the nop command supported
				drive->cmd_set_supported[NOP_SUPPORTED].supported = supported;
				break;
			}
			case 13: {
				//is the read buffer command supported
				drive->cmd_set_supported[READ_BUFFER_SUPPORTED].supported = supported;
				break;
			}
			case 12: {
				//is the write buffer command supported
				drive->cmd_set_supported[WRITE_BUFFER_SUPPORTED].supported = supported;
				break;
			}
			case 11: {
				//this is not used
				continue;
			}
			case 10: {
				//is the host protected area supported
				drive->cmd_set_supported[HOST_PROTECTED_AREA_SUPPORTED].supported = supported;
				break;
			}
			case 9: {
				//is the reset command supported
				drive->cmd_set_supported[DEVICE_RESET_SUPPORTED].supported = supported;
				break;
			}
			case 8: {
				//is service interrupt is supported
				drive->cmd_set_supported[SERVICE_INTERRUPT_SUPPORTED].supported = supported;
				break;
			}
			case 7: {
				//is release interrupt supported
				drive->cmd_set_supported[RELEASE_INTERRUPT_SUPPORTED].supported = supported;
				break;
			}
			case 6: {
				//is look ahead supported
				drive->cmd_set_supported[LOOK_AHEAD_SUPPORTED].supported = supported;
				break;
			}
			case 5: {
				//is the write cache command supported
				drive->cmd_set_supported[WRITE_CACHE_SUPPORTED].supported = supported;
				break;
			}
			case 4: {
				//is the packet command supported
				drive->cmd_set_supported[PACKET_COMMAND_SUPPORTED].supported = supported;
				break;
			}
			case 3: {
				//is the power management set supported
				drive->cmd_set_supported[POWER_MANAGEMENT_SET_SUPPORTED].supported = supported;
				break;
			}
			case 2: {
				//is the removable device set supported
				drive->cmd_set_supported[REMOVABLE_DEVICE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 1: {
				//is the security mode feature set supported
				drive->cmd_set_supported[SECURITY_MODE_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 0: {
				//is SMART feature set supported
				drive->cmd_set_supported[SMART_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			default: {
				//not anything
				break;
			}
		}
	}
}