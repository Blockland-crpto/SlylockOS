#include <shell.h>
#include <drivers/acpi.h>

void shutdown() {
  acpiPowerOff();
}