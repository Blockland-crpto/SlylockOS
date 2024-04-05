#include <errno.h>
#include <libc.h>
#include <system/modules.h>

void libc_init() {
	module_t modules_libc = MODULE("kernel.modules.libc", "Defines the C standard library from http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf for convenient use.");
	INIT(modules_libc);
	errno_init();
	DONE(modules_libc);
}