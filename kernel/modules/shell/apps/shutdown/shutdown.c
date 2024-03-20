#include <shell/shell.h>
#include <drivers/acpi.h>
#include <libtui.h>

void shutdown() {
  loadingscreen("Shutting Down", "MiniOS is Shutting down...");

  acpiPowerOff();
}