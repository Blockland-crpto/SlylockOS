#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <libmodule.h>
#include <libssp.h>

//ATA initializer
void ata_init() {
	module_t modules_ata = MODULE("kernel.modules.ata", "Provides ATA support for the kernel, read/write (CORE)");

	//let the initalization begin!
	INIT(modules_ata);

	//lets register the master drive
	ata_device_t master = ata_identify(SELECT_DEVICE_MASTER);

	//lets get the slave device
	ata_device_t slave = ata_identify(SELECT_DEVICE_SLAVE);

	//does the master exist?
	if (master.exists == false) {

		//it doesn't error out
		FAIL(modules_ata, "Master ATA drive does not exist");
	} else {

		//it does exist
		ata_drives[0] = master;

		//were done!
		DONE(modules_ata);
	}
	
}