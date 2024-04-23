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