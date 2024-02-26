#include <shell.h>
#include <drivers/acpi.h>
#include <gui.h>

void shutdown() {
  loadingscreen("Shutting Down", "MiniOS is Shutting down...");
  acpiPowerOff();
}