#ifndef __DRIVERS_ACPI_H__
#define __DRIVERS_ACPI_H__

#include <system/types.h>


unsigned long *SMI_CMD;
signed char ACPI_ENABLE;
signed char ACPI_DISABLE;
unsigned long *PM1a_CNT;
unsigned long *PM1b_CNT;
uint16_t SLP_TYPa;
uint16_t SLP_TYPb;
uint16_t SLP_EN;
uint16_t SCI_EN;
signed char PM1_CNT_LEN;

struct RSDPtr {
   signed char Signature[8];
   signed char CheckSum;
   signed char OemID[6];
   signed char Revision;
   unsigned long *RsdtAddress;
};

struct FACP {
   signed char Signature[4];
   unsigned long Length;
   signed char unneded1[40 - 8];
   unsigned long *DSDT;
   signed char unneded2[48 - 44];
   unsigned long *SMI_CMD;
   signed char ACPI_ENABLE;
   signed char ACPI_DISABLE;
   signed char unneded3[64 - 54];
   unsigned long *PM1a_CNT_BLK;
   unsigned long *PM1b_CNT_BLK;
   signed char unneded4[89 - 72];
   signed char PM1_CNT_LEN;
};

struct MADT {
   signed char Signature[4];
   unsigned long Length;
   signed char Revision;
   signed char CheckSum;
   signed char OemID[6];
   uint32_t localApicAddr;
};

unsigned int *acpiCheckRSDPtr(uint32_t *ptr);
unsigned int *acpiGetRSDPtr(void);
int acpiCheckHeader(uint32_t *ptr, char *sig);
int acpiEnable(void);
int initAcpi(void);
void acpiPowerOff(void);
void acpi_init();
bool acpiEnabled;


#endif