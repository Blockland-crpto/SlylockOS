#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>
#include <cmdset.h>

//helpers
extern void ata_id_setup();
extern void get_drive_config();
extern void get_drive_vendor();
extern void	get_drive_capabilities();
extern void get_drive_ata_version();
extern void get_drive_sect_valid();

//helpers for dma information
extern void get_drive_mdma_support();
extern void get_drive_udma_support();

//helpers for command set retrieval
extern void get_drive_cmd_set_1();
extern void get_drive_cmd_set_2();
extern void get_drive_cmd_set_ext();

//helpers for enabled features retrieval
extern void get_drive_cmd_set_enabled();
extern void get_drive_cmd_set_enabled_2();

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
	static volatile uint16_t identify_data[256];

	//lets get the data
	for (size_t i = 0; i < 256; i++) {
		identify_data[i] = inw(IO_PORT_DATA);
	}

	//lets get the drive config data
	get_drive_config(&drive, identify_data);

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
	bool valid_sect_1 = (validity_section & (1 << 1)) ? true : false; // is 64-70 valid?
	bool valid_sect_2 = (validity_section & (1 << 2)) ? true : false; // is 88 valid?

	//lets get the ata specific data
	if (!drive.atapi_info.is_atapi) {
		//lets find the number of 28 bit addressable space
		uint16_t addressable_space_1 = identify_data[60];
		uint16_t addressable_space_2 = identify_data[61];
		uint32_t addressable_space_lba28 = (addressable_space_2 << 8) | addressable_space_1;

		if ((addressable_space_lba28 & 0x00)) {
			drive.lba28_enabled = false;
		} else {
			drive.addressable_space_lba28 = addressable_space_lba28;
		}
	}
	

	//lets find mdma mode
	get_drive_mdma_support(&drive, identify_data);

	//lets check if the above is valid
	if (valid_sect_1) {
		//call the function
		get_drive_sect_valid(&drive, identify_data);
	}
	
	//lets retrieve the queue depth
	uint16_t queue_depth_raw = identify_data[75];
	
	//lets get the queue depth
	drive.max_queue_depth = queue_depth_raw & 0x1F;

	//gets ata version
	get_drive_ata_version(&drive, identify_data);

	//gets ata command set
	get_drive_cmd_set_1(&drive, identify_data);

	// for loop to validate these two variabled
	for (int i = 83; i < 85; i++) {
		//lets validate!
		uint16_t command_check = identify_data[i];

		//first lets see if its valid
		if ((command_check & (1 << 15)) == 1) {
			//its not valid, error out
			drive.exists = false;
			return drive;
		}
	}
	
	//gets ata command set 2
	get_drive_cmd_set_2(&drive, identify_data);

	//gets ata command set ext
	get_drive_cmd_set_ext(&drive, identify_data);

	//gets the drive cmd set enabled
	get_drive_cmd_set_enabled(&drive, identify_data);

	//gets the second drive cmd set enabled
	get_drive_cmd_set_enabled_2(&drive, identify_data);
	
	//gets the drive udma support
	get_drive_udma_support(&drive, identify_data);

	//lets get time required for security erase completion
	drive.time_required_for_security_erase = identify_data[89];

	//lets get time required for erase completion enhanced
	drive.time_required_secure_erase_enhanced = identify_data[90];

	//lets get current APM value
	drive.current_apm_value = identify_data[91];

	//lets get the master password rev code
	drive.master_password_revision_code = identify_data[92];
	
	//lets find out if it uses a 80-pin cable
	uint16_t cable_type = identify_data[93];

	//it a 80-pin cable
	if ((cable_type & (1 << 11)) == 1) {
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

	if ((addressable_space_lba48 & 0x00) == 1) {
		drive.lba48_enabled = false;
	} else {
		drive.addressable_space_lba48 = addressable_space_lba48;
	}
	
	drive.exists = true;
	drive.identify_data_ptr = &identify_data;
	return drive;
}