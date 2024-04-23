#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//function to iterate through the drives mdma support
void get_drive_mdma_support(ata_device_t* drive, uint16_t* identify_data) {
	
	//for loop to iterate over the supported MDMA's
	for (int i = 0; i < 3; i++) {

		//lets reset the variable
		uint16_t mdma_mode = identify_data[63];

		if ((mdma_mode & (1 << i)) == 1) {
			//the mdma mode is supported
			mdma_mode_t mdma;
			mdma.supported = true;
			mdma.id = i;
			drive->supported_mdma[i] = mdma;
		} else {
			//the mdma mode is not supported
			mdma_mode_t mdma;
			mdma.supported = false;
			mdma.id = i;
			drive->supported_mdma[i] = mdma;
		}

		//lets reset the variable
		mdma_mode = identify_data[63];
		
		uint8_t active_mdma_bits = (uint8_t)(mdma_mode >> 8);

		if ((active_mdma_bits & (1 << i)) == 1) {
			//the udma mode is being used
			drive->active_mdma = drive->supported_mdma[i];
		}
	}
}