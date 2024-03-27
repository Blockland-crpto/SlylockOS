#include <drivers/io/ata.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <system/modules.h>
#include <libssp.h>

//Resets ATA
void ata_reset() {
	
	outb(CTRL_DEVICE, DEV_CTRL_SRST);
	outb(CTRL_DEVICE, 0x00);
	outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_SLAVE);
	outb(CTRL_DEVICE, 0x00);
	outb(IO_PORT_DRIVE_HEAD, SELECT_DEVICE_MASTER);
	return;
}