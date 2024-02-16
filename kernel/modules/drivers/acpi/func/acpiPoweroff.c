#include <ports.h>
#include <screen.h>
#include <types.h>
#include <drivers/acpi.h>


void acpiPowerOff(void) {
   // SCI_EN is set to 1 if acpi shutdown is possible
   if (SCI_EN == 0)
	  return;

   acpiEnable();

   // send the shutdown command
   outw((uint32_t) PM1a_CNT, SLP_TYPa | SLP_EN );
   if ( PM1b_CNT != 0 )
	  outw((uint32_t) PM1b_CNT, SLP_TYPb | SLP_EN );

   kprintf("acpi poweroff failed.\n");
}