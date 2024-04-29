#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//function to get the drive cmd set 2
void get_drive_cmd_set_enabled(ata_device_t* drive, uint16_t* identify_data) {
	//lets now get word 85
	uint16_t command_sets_enabled = identify_data[85];

	//for loop to iterate through the word
	for (int i = 14; i >= 0; i--) {

		//lets reset the compare variable
		command_sets_enabled = identify_data[85];
		
		//enabled bool
		bool enabled = (command_sets_enabled & (1 << i)) ? true : false;

		//switched the mask
		switch(i) {
			case 14: {
				//is the nop command enabled
				drive->cmd_set_supported[NOP_SUPPORTED].enabled = enabled;
				break;
			}
			case 13: {
				//is the read buffer command enabled
				drive->cmd_set_supported[READ_BUFFER_SUPPORTED].enabled = enabled;
				break;
			}
			case 12: {
				//is the write buffer command enabled
				drive->cmd_set_supported[WRITE_BUFFER_SUPPORTED].enabled = enabled;
				break;
			}
			case 10: {
				//is the host protected area enabled
				drive->cmd_set_supported[HOST_PROTECTED_AREA_SUPPORTED].enabled = enabled;
				break;
			}
			case 9: {
				//is the reset command enabled
				drive->cmd_set_supported[DEVICE_RESET_SUPPORTED].enabled = enabled;
				break;
			}
			case 8: {
				//is service interrupt is enabled
				drive->cmd_set_supported[SERVICE_INTERRUPT_SUPPORTED].enabled = enabled;
				break;
			}
			case 7: {
				//is release interrupt enabled
				drive->cmd_set_supported[RELEASE_INTERRUPT_SUPPORTED].enabled = enabled;
				break;
			}
			case 6: {
				//is look ahead enabled
				drive->cmd_set_supported[LOOK_AHEAD_SUPPORTED].enabled = enabled;
				break;
			}
			case 5: {
				//is the write cache command enabled
				drive->cmd_set_supported[WRITE_CACHE_SUPPORTED].enabled = enabled;
				break;
			}
			case 3: {
				//is the power management set enabled
				drive->cmd_set_supported[POWER_MANAGEMENT_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 2: {
				//is the removable device set enabled
				drive->cmd_set_supported[REMOVABLE_DEVICE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 1: {
				//is the security mode feature set enabled
				drive->cmd_set_supported[SECURITY_MODE_FEATURE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 0: {
				//is SMART feature set enabled
				drive->cmd_set_supported[SMART_FEATURE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			default: {
				//not anything
				break;
			}
		}
	}

}