#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <system/modules.h>
#include <libssp.h>

//Resets ATA
void ata_reset() {
	//todo: use device reset command to reset if able to
	//lets check if the ATA supports device reset
	if (!ata_drives[0].cmd_set_supported[DEVICE_RESET_SUPPORTED]) {
		//no support
		return;
	}
	outb(CTRL_DEVICE, DEV_CTRL_SRST);
	outb(CTRL_DEVICE, 0x00);
	outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_SLAVE);
	outb(CTRL_DEVICE, 0x00);
	outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_MASTER);
	return;
}