#include <errno.h>
#include <libc.h>
#include <system/modules.h>

void libc_init() {
	module_t modules_libc_libc = MODULE("kernel.modules.libc.libc", "Defines the C standard library from http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf for convenient use. Please do note that printf is included in screen.h, not stdio.h.");
	INIT(modules_libc_libc);
	errno_init();
	DONE(modules_libc_libc);
}