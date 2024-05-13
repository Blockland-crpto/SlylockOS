/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
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
	ata_device_t slave __attribute__((unused)) = ata_identify(SELECT_DEVICE_SLAVE);

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