#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>

//put ATA in standby mode
void ata_standby() {
	
	//check to see if ready
	wait_ata_bsy();

	//todo: error check

	//send standby command to command port
	outb(IO_PORT_COMMAND, DRIVE_STANDBY);
	
}