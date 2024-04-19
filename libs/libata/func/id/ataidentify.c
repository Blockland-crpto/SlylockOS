#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//helpers
extern void ata_id_setup();
extern void get_drive_config();
extern void get_drive_vendor();
extern void	get_drive_capabilities();
extern void get_drive_ata_version();

//sends the identify command to the ata device, reads it, and parses it
ata_device_t ata_identify(enum ata_device_select dev) {

	//creates a structure to represent a ATA drive
	ata_device_t drive;

	//call the setup function
	ata_id_setup(&drive, dev);

	//lets check if its still a valid drive
	if (!drive.exists) {
		//drive does not exist
		return drive;
	}
	
	//the drive is ready to be read
	uint16_t identify_data[256];
	
	for (size_t i = 0; i < 256; i++) {
		identify_data[i] = inw(IO_PORT_DATA);
	}

	//lets get the drive config data
	get_drive_config(&drive, identify_data[0]);

	//lets check if its still a valid drive
	if (!drive.exists) {
		//drive does not exist
		return drive;
	}

	//lets get vendor information
	get_drive_vendor(&drive, identify_data);

	//next lets get the sectors per interrupt in read write multiple
	drive.sectors_per_interrupt_rw_multiple = (uint8_t)identify_data[47];

	//lets get the capabilities
	get_drive_capabilities(&drive, identify_data);
	
	//next lets look at 53 to see which are valid in the next few things
	uint16_t validity_section = identify_data[53];

	//we should also define some bools to check if the drives sections are valid
	bool valid_sect_1; // is 64-70 valid?
	bool valid_sect_2; // is 88 valid?
	
	//64-70 validity mask
	uint16_t validity_mask = 1 << 1;

	//now lets check if the first section is valid

	//lets check it!
	if (validity_section&validity_mask) {
		//the section is valid
		valid_sect_1 = true;
	} else {
		//the section is not valid
		valid_sect_1 = false;
	}

	//lets check if the second section is valid
	//the new mask
	validity_mask = 1 << 2;

	//lets check it!
	if (validity_section&validity_mask) {
		//the section is valid
		valid_sect_2 = true;
	} else {
		//the section is not valid
		valid_sect_2 = false;
	}
	
	//lets find the number of 28 bit addressable space
	uint16_t addressable_space_1 = identify_data[60];
	uint16_t addressable_space_2 = identify_data[61];
	uint32_t addressable_space_lba28 = (addressable_space_2 << 8) | addressable_space_1;

	if (addressable_space_lba28&0x00) {
		drive.lba28_enabled = false;
	} else {
		drive.addressable_space_lba28 = addressable_space_lba28;
	}

	//lets find the MDMA mode
	uint16_t mdma_mode = identify_data[63];

	//for loop to iterate over the supported MDMA's
	for (int i = 0; i < 3; i++) {
		//mdma mask
		uint16_t mdma_mode_mask = 1 << i;

		if (mdma_mode&mdma_mode_mask) {
			//the mdma mode is supported
			mdma_mode_t mdma;
			mdma.supported = true;
			mdma.id = i;
			drive.supported_mdma[i] = mdma;
		} else {
			//the mdma mode is not supported
			mdma_mode_t mdma;
			mdma.supported = false;
			mdma.id = i;
			drive.supported_mdma[i] = mdma;
		}

		uint8_t active_mdma_bits = (uint8_t)(mdma_mode >> 8);

		if (active_mdma_bits&(1 << i)) {
			//the udma mode is being used
			drive.active_mdma = drive.supported_mdma[i];
		}
	}

	//lets check if the above is valid
	if (valid_sect_1) {
		//lets get the supported pio modes
		uint16_t pio_mode = identify_data[64];

		//lets see the pio mask
		uint16_t pio_mode_mask;

		//iterate through supported pio modes
		for (int i = 0; i < 7; i++) {
			//pio mask
			pio_mode_mask = 1 << i;

			//lets check it!
			if (pio_mode&pio_mode_mask) {
				//it is supported
				pio_mode_t pio;
				pio.supported = true;
				pio.id = i;
				drive.supported_pio[i] = pio;
			} else {
				//it is not supported
				pio_mode_t pio;
				pio.supported = false;
				pio.id = i;
				drive.supported_pio[i] = pio;
			}
		}

		//lets get the minimum mdma transfer per word
		drive.min_mdma_transfer_time_per_word = identify_data[65];

		//lets get the manufactures recommended min mda transfer time
		drive.min_mdma_transfer_time_vendor = identify_data[66];

		//lets get the minimum pio transfer time without flow control
		drive.min_pio_transfer_time_no_flow_ctrl = identify_data[67];

		//lets get the minimum pio transfer time with flow control
		drive.min_pio_transfer_time_iordy_flow_ctrl = identify_data[68];
	}
	
	//lets retrieve the queue depth
	uint16_t queue_depth_raw = identify_data[75];
	
	//lets get the queue depth
	drive.max_queue_depth = queue_depth_raw & 0x1F;

	//gets ata version
	get_drive_ata_version(&drive, identify_data);

	//now lets look at the first command set
	uint16_t command_sets1 = identify_data[82];

	//for loop to iterate through the word
	for (int i = 14; i >= 0; i--) {

		//supported bool
		bool supported;
		
		//the mask
		uint16_t command_set_mask = 1 << i;

		//is it supported?
		if (command_sets1&command_set_mask) {
			//it is supported
			supported = true;
		} else {
			//it is not supported
			supported = false;
		}
		
		//switched the mask
		switch(i) {
			case 14: {
				//is the nop command supported
				drive.cmd_set_supported[NOP_SUPPORTED].supported = supported;
				break;
			}
			case 13: {
				//is the read buffer command supported
				drive.cmd_set_supported[READ_BUFFER_SUPPORTED].supported = supported;
				break;
			}
			case 12: {
				//is the write buffer command supported
				drive.cmd_set_supported[WRITE_BUFFER_SUPPORTED].supported = supported;
				break;
			}
			case 10: {
				//is the host protected area supported
				drive.cmd_set_supported[HOST_PROTECTED_AREA_SUPPORTED].supported = supported;
				break;
			}
			case 9: {
				//is the reset command supported
				drive.cmd_set_supported[DEVICE_RESET_SUPPORTED].supported = supported;
				break;
			}
			case 8: {
				//is service interrupt is supported
				drive.cmd_set_supported[SERVICE_INTERRUPT_SUPPORTED].supported = supported;
				break;
			}
			case 7: {
				//is release interrupt supported
				drive.cmd_set_supported[RELEASE_INTERRUPT_SUPPORTED].supported = supported;
				break;
			}
			case 6: {
				//is look ahead supported
				drive.cmd_set_supported[LOOK_AHEAD_SUPPORTED].supported = supported;
				break;
			}
			case 5: {
				//is the write cache command supported
				drive.cmd_set_supported[WRITE_CACHE_SUPPORTED].supported = supported;
				break;
			}
			case 4: {
				//is the packet command supported
				drive.cmd_set_supported[PACKET_COMMAND_SUPPORTED].supported = supported;
				break;
			}
			case 3: {
				//is the power management set supported
				drive.cmd_set_supported[POWER_MANAGEMENT_SET_SUPPORTED].supported = supported;
				break;
			}
			case 2: {
				//is the removable device set supported
				drive.cmd_set_supported[REMOVABLE_DEVICE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 1: {
				//is the security mode feature set supported
				drive.cmd_set_supported[SECURITY_MODE_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 0: {
				//is SMART feature set supported
				drive.cmd_set_supported[SMART_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			default: {
				//not anything
				break;
			}
		}
	}
	
	//now lets look at the command sets 2
	uint16_t command_sets2 = identify_data[83];

	//first lets check to see if its valid
	uint16_t command_sets2_validity_mask = 1 << 15;
	
	//lets check it!
	if (command_sets2&command_sets2_validity_mask) {
		//it's not valid, the 15th bit is set to 1 instead of 0
		drive.exists = false;
		return drive;
	}
	
	//for loop to iterate through the word
	for (int i = 13; i >= 0; i--) {

		//supported bool
		bool supported;

		//the mask
		uint16_t command_set_mask = 1 << i;

		//is it supported?
		if (command_sets2&command_set_mask) {
			//it is supported
			supported = true;
		} else {
			//it is not supported
			supported = false;
		}

		//switched the mask
		switch(i) {
			case 13: {
				//is the FLUSH CACHE EXT command supported
				drive.cmd_set_supported[FLUSH_CACHE_EXT_SUPPORTED].supported = supported;
				break;
			}
			case 12: {
				//is the mandatory FLUSH CACHE command supported
				drive.cmd_set_supported[MANDATORY_FLUSH_CACHE_SUPPORTED].supported = supported;
				break;
			}
			case 11: {
				//is the device configuration overlay feature set supported
				drive.cmd_set_supported[DEVICE_CONFIG_OVERLAY_SUPPORTED].supported = supported;
				break;
			}
			case 10: {
				//is the 48 bit address feature set supported
				drive.cmd_set_supported[LBA48_ENABLED].supported = supported;
				break;
			}
			case 9: {
				//is automatic acoustic management supported
				drive.cmd_set_supported[AUTO_ACOUSTIC_MANAGEMENT_SUPPORTED].supported = supported;
				break;
			}
			case 8: {
				//is SET MAX security extentsion supported
				drive.cmd_set_supported[SET_MAX_SECURITY_EXTENTSION_SUPPORTED].supported = supported;
				break;
			}
			case 6: {
				//is drive spin up required for set features after power up?
				drive.set_features_spinup_needed = supported;
				break;
			}
			case 5: {
				//is power up in standby supported
				drive.cmd_set_supported[POWER_UP_IN_STANDBY_SUPPORTED].supported = supported;
				break;
			}
			case 4: {
				//is removable media status notification supported
				drive.cmd_set_supported[REMOVEABLE_MEDIA_STATUS_SUPPORTED].supported = supported;
				break;
			}
			case 3: {
				//is the advanced power management set supported
				drive.cmd_set_supported[ADVANCED_POWER_MANAGEMENT_SUPPORTED].supported = supported;
				break;
			}
			case 2: {
				//is the CFA feature set supported
				drive.cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 1: {
				//is READ/WRITE DMA QUEUED command supported
				drive.cmd_set_supported[READ_WRITE_DMA_QUEUED_SUPPORTED].supported = supported;
				break;
			}
			case 0: {
				//is DOWNLOAD MICROCODE command supported
				drive.cmd_set_supported[DOWNLOAD_MICROCODE_SUPPORTED].supported = supported;
				break;
			}
			default: {
				//nothing
				break;
			}
		}
	}

	//now lets look the command set extentsion
	uint16_t command_sets_ext = identify_data[84];

	//first lets see if its valid
	uint16_t command_sets_ext_validity_mask = 1 << 15;
	
	//lets check it!
	if (command_sets_ext&command_sets_ext_validity_mask) {
		//its not valid, error out
		drive.exists = false;
		return drive;
	}

	//for loop to iterate through the word
	for (int i = 10; i >= 0; i--) {

		//supported bool
		bool supported;

		//the mask
		uint16_t command_set_mask = 1 << i;

		//is it supported?
		if (command_sets_ext&command_set_mask) {
			//it is supported
			supported = true;
		} else {
			//it is not supported
			supported = false;
		}

		//switched the mask
		switch(i) {
			case 10: {
				//is the URG bit supported for WRITE STREAM DMA or PIO
				drive.cmd_set_supported[URG_WRITE_BIT_SUPPORTED].supported = supported;
				break;
			}
			case 9: {
				//is the URG bit supported for READ STREAM DMA or PIO
				drive.cmd_set_supported[URG_READ_BIT_SUPPORTED].supported = supported;
				break;
			}
			case 8: {
				//is world wide name supported?
				drive.cmd_set_supported[WORLD_WIDE_NAME_SUPPORTED].supported = supported;
				break;
			}
			case 7: {
				//is WRITE DMA QUEUED FUA EXT command supported 
				drive.cmd_set_supported[WRITE_DMA_QUEUED_FUA_EXT_SUPPORTED].supported = supported;
				break;
			}
			case 6: {
				//is WRITE DMA FUA EXT and WRITE MULTIPLE FUA EXT commands supported?
				drive.cmd_set_supported[WRITE_DMA_FUA_EXT_AND_WRITE_MULTIPLE_FUA_EXT].supported = supported;
				break;
			}
			case 5: {
				//is the general purpose logging feature set supported?
				drive.cmd_set_supported[GENERAL_PURPOSE_LOGING_SUPPORTED].supported = supported;
				break;
			}
			case 4: {
				//is the streaming feature set supported?
				drive.cmd_set_supported[STREAMING_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 3: {
				//is media card pass through supported?
				drive.cmd_set_supported[MEDIA_CARD_PASSTHROUGH_SUPPORTED].supported = supported;
				break;
			}
			case 2: {
				//is media serial number supported?
				drive.cmd_set_supported[MEDIA_SERIAL_NUMBER_SUPPORTED].supported = supported;
				break;
			}
			case 1: {
				//is SMART self test supported?
				drive.cmd_set_supported[SMART_SELF_TEST_SUPPORTED].supported = supported;
				break;
			}
			case 0: {
				//is SMART error logging supported?
				drive.cmd_set_supported[SMART_ERROR_LOGGING_SUPPORTED].supported = supported;
			}
			default: {
				//should error out
				break;
			}
		}
	}


	//lets now get word 85
	uint16_t command_sets_enabled = identify_data[85];

	//for loop to iterate through the word
	for (int i = 14; i >= 0; i--) {

		//enabled bool
		bool enabled;

		//the mask
		uint16_t command_set_mask = 1 << i;

		//is it enabled?
		if (command_sets1&command_set_mask) {
			//it is enabled
			enabled = true;
		} else {
			//it is not enabled
			enabled = false;
		}

		//switched the mask
		switch(i) {
			case 14: {
				//is the nop command enabled
				drive.cmd_set_supported[NOP_SUPPORTED].enabled = enabled;
				break;
			}
			case 13: {
				//is the read buffer command enabled
				drive.cmd_set_supported[READ_BUFFER_SUPPORTED].enabled = enabled;
				break;
			}
			case 12: {
				//is the write buffer command enabled
				drive.cmd_set_supported[WRITE_BUFFER_SUPPORTED].enabled = enabled;
				break;
			}
			case 10: {
				//is the host protected area enabled
				drive.cmd_set_supported[HOST_PROTECTED_AREA_SUPPORTED].enabled = enabled;
				break;
			}
			case 9: {
				//is the reset command enabled
				drive.cmd_set_supported[DEVICE_RESET_SUPPORTED].enabled = enabled;
				break;
			}
			case 8: {
				//is service interrupt is enabled
				drive.cmd_set_supported[SERVICE_INTERRUPT_SUPPORTED].enabled = enabled;
				break;
			}
			case 7: {
				//is release interrupt enabled
				drive.cmd_set_supported[RELEASE_INTERRUPT_SUPPORTED].enabled = enabled;
				break;
			}
			case 6: {
				//is look ahead enabled
				drive.cmd_set_supported[LOOK_AHEAD_SUPPORTED].enabled = enabled;
				break;
			}
			case 5: {
				//is the write cache command enabled
				drive.cmd_set_supported[WRITE_CACHE_SUPPORTED].enabled = enabled;
				break;
			}
			case 3: {
				//is the power management set enabled
				drive.cmd_set_supported[POWER_MANAGEMENT_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 2: {
				//is the removable device set enabled
				drive.cmd_set_supported[REMOVABLE_DEVICE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 1: {
				//is the security mode feature set enabled
				drive.cmd_set_supported[SECURITY_MODE_FEATURE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 0: {
				//is SMART feature set enabled
				drive.cmd_set_supported[SMART_FEATURE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			default: {
				//not anything
				break;
			}
		}
	}
	
	//lets see the UDMA modes
	uint16_t udma_mode = identify_data[88];

	//for loop to iterate over the supported UDMA's
	for (int i = 0; i < 8; i++) {
		//udma mask
		uint16_t udma_mode_mask = 1 << i;
		
		if (udma_mode&udma_mode_mask) {
			//the udma mode is supported
			udma_mode_t udma;
			udma.supported = true;
			udma.id = i;
			drive.supported_udma[i] = udma;
		} else {
			//the udma mode is not supported
			udma_mode_t udma;
			udma.supported = false;
			udma.id = i;
			drive.supported_udma[i] = udma;
		}

		//lets define the active bits of UDMA
		uint8_t active_udma_bits = (uint8_t)(udma_mode >> 8);

		if (active_udma_bits&(1 << i)) {
			//the udma mode is being used
			drive.active_udma = drive.supported_udma[i];
		}
	}

	//lets find out if it uses a 80-pin cable
	uint16_t cable_type = identify_data[93];
	uint16_t cable_type_mask = 1 << 11;

	//it a 80-pin cable
	if (cable_type&cable_type_mask) {
		drive.pin80_connector = true;
	} else {
		drive.pin80_connector = false;
	}

	//lets find the number of 48 bit addressable space
	uint16_t addressable_space_3 = identify_data[100];
	uint16_t addressable_space_4 = identify_data[101];
	uint16_t addressable_space_5 = identify_data[102];
	uint16_t addressable_space_6 = identify_data[103];
	uint64_t addressable_space_lba48 = ((uint64_t)addressable_space_3 << 48) | ((uint64_t)addressable_space_4 << 32) | ((uint64_t)addressable_space_5 << 16) | addressable_space_6;

	if (addressable_space_lba48&0x00) {
		drive.lba48_enabled = false;
	} else {
		drive.addressable_space_lba48 = addressable_space_lba48;
	}
	
	drive.exists = true;
	return drive;
}