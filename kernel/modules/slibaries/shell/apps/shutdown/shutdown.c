#include <slibaries/shell.h>
#include <drivers/acpi.h>
#include <slibaries/gui.h>

void shutdown() {
  loadingscreen("Shutting Down", "MiniOS is Shutting down...");
  acpiPowerOff();
}