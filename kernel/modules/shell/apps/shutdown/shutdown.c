#include <shell.h>
#include <drivers/acpi.h>
#include <gui.h>

void shutdown() {
  shutdown_screen();
  acpiPowerOff();
}