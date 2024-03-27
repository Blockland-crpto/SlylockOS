#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>

//ATA error handler
void ata_error_handler() {
	uint8_t error = inb(IO_PORT_ERROR);
	warn("ATA error occured ");
	warn(error);
	if (error & ERROR_AMNF) {
		//todo: implement a ata not found error handler
	} else if (error & ERROR_TKZNF) {
		//todo: implement a ata track zero not found error handler
	} else if (error & ERROR_ABRT) {
		//todo: implement a ata abort error handler
	} else if (error & ERROR_MCR) {
		//todo: implement a ata media change request error handler
	} else if (error & ERROR_IDNF) {
		//todo: implement a ata id not found error handler
	} else if (error & ERROR_MC) {
		//todo: implement a ata media change error handler
	} else if (error & ERROR_UNC) {
		//todo: implement a ata uncorrectable error handler
	} else if (error & ERROR_BBK) {
		//todo: implement a ata bad block error handler
	}
}