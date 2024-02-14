/**
  \file      drivers.h
  \brief     drivers
  \details   This header file is used as a general compilations of the drivers
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/
 

#ifndef __DRIVERS_H

#define __DRIVERS_H

#include <types.h>
#include <stdint.h>
#include <stddef.h>
#include <screen.h>

/** ATA DRIVER START **/
#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01
void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint8_t sector_count);
void sect_write_atapio(uint32_t LBA, uint8_t sector_count, uint32_t* bytes);
static void wait_ata_bsy();
static void wait_ata_drq();
/** ATA DRIVER END **/



/** VIDEO DRIVER START **/
enum video_type {
	VIDEO_TYPE_NONE = 0x00,
	VIDEO_TYPE_COLOR = 0x20,
	VIDEO_TYPE_MONOCHROME = 0x30,
};
uint16_t detect_bios_area_hardware();
enum video_type get_bios_area_video_type();
/** VIDEO DRIVER END **/



/** ACPI DRIVER START **/
dword *SMI_CMD;
byte ACPI_ENABLE;
byte ACPI_DISABLE;
dword *PM1a_CNT;
dword *PM1b_CNT;
word SLP_TYPa;
word SLP_TYPb;
word SLP_EN;
word SCI_EN;
byte PM1_CNT_LEN;
struct RSDPtr {
   byte Signature[8];
   byte CheckSum;
   byte OemID[6];
   byte Revision;
   dword *RsdtAddress;
};
struct FACP {
   byte Signature[4];
   dword Length;
   byte unneded1[40 - 8];
   dword *DSDT;
   byte unneded2[48 - 44];
   dword *SMI_CMD;
   byte ACPI_ENABLE;
   byte ACPI_DISABLE;
   byte unneded3[64 - 54];
   dword *PM1a_CNT_BLK;
   dword *PM1b_CNT_BLK;
   byte unneded4[89 - 72];
   byte PM1_CNT_LEN;
};
unsigned int *acpiCheckRSDPtr(unsigned int *ptr);
unsigned int *acpiGetRSDPtr(void);
int acpiCheckHeader(unsigned int *ptr, char *sig);
int acpiEnable(void);
int initAcpi(void);
void acpiPowerOff(void);
void acpi_init();
int acpiEnabled;
/** ACPI DRIVER END **/



/** MMIO DRIVER START **/
class MMIOUtils {
	public:
		static uint8_t read8 (uint64_t p_address);
		static uint16_t read16 (uint64_t p_address);
		static uint32_t read32 (uint64_t p_address);
		static uint64_t read64 (uint64_t p_address);
		static void write8 (uint64_t p_address,uint8_t p_value);
		static void write16 (uint64_t p_address,uint16_t p_value);
		static void write32 (uint64_t p_address,uint32_t p_value);
		static void write64 (uint64_t p_address,uint64_t p_value);
};
uint8_t MMIOUtils::read8 (uint64_t p_address) {
	return *((volatile uint8_t*)(p_address));
}
uint16_t MMIOUtils::read16 (uint64_t p_address) {
	return *((volatile uint16_t*)(p_address));

}
uint32_t MMIOUtils::read32 (uint64_t p_address) {
	return *((volatile uint32_t*)(p_address));

}
uint64_t MMIOUtils::read64 (uint64_t p_address) {
	return *((volatile uint64_t*)(p_address));    
}
void MMIOUtils::write8 (uint64_t p_address,uint8_t p_value) {
	(*((volatile uint8_t*)(p_address)))=(p_value);
}
void MMIOUtils::write16 (uint64_t p_address,uint16_t p_value) {
	(*((volatile uint16_t*)(p_address)))=(p_value);    
}
void MMIOUtils::write32 (uint64_t p_address,uint32_t p_value) {
	(*((volatile uint32_t*)(p_address)))=(p_value);
}
void MMIOUtils::write64 (uint64_t p_address,uint64_t p_value) {
	(*((volatile uint64_t*)(p_address)))=(p_value);    
}
/** MMIO DRIVER END **/



/** INTEL ETHERNET i217 DRIVER BEGIN **/
#define INTEL_VEND     0x8086  // Vendor ID for Intel 
#define E1000_DEV      0x100E  // Device ID for the e1000 Qemu, Bochs, and VirtualBox emmulated NICs
#define E1000_I217     0x153A  // Device ID for Intel I217
#define E1000_82577LM  0x10EA  // Device ID for Intel 82577LM


// I have gathered those from different Hobby online operating systems instead of getting them one by one from the manual

#define REG_CTRL        0x0000
#define REG_STATUS      0x0008
#define REG_EEPROM      0x0014
#define REG_CTRL_EXT    0x0018
#define REG_IMASK       0x00D0
#define REG_RCTRL       0x0100
#define REG_RXDESCLO    0x2800
#define REG_RXDESCHI    0x2804
#define REG_RXDESCLEN   0x2808
#define REG_RXDESCHEAD  0x2810
#define REG_RXDESCTAIL  0x2818

#define REG_TCTRL       0x0400
#define REG_TXDESCLO    0x3800
#define REG_TXDESCHI    0x3804
#define REG_TXDESCLEN   0x3808
#define REG_TXDESCHEAD  0x3810
#define REG_TXDESCTAIL  0x3818


#define REG_RDTR         0x2820 // RX Delay Timer Register
#define REG_RXDCTL       0x2828 // RX Descriptor Control
#define REG_RADV         0x282C // RX Int. Absolute Delay Timer
#define REG_RSRPD        0x2C00 // RX Small Packet Detect Interrupt



#define REG_TIPG         0x0410      // Transmit Inter Packet Gap
#define ECTRL_SLU        0x40        //set link up


#define RCTL_EN                         (1 << 1)    // Receiver Enable
#define RCTL_SBP                        (1 << 2)    // Store Bad Packets
#define RCTL_UPE                        (1 << 3)    // Unicast Promiscuous Enabled
#define RCTL_MPE                        (1 << 4)    // Multicast Promiscuous Enabled
#define RCTL_LPE                        (1 << 5)    // Long Packet Reception Enable
#define RCTL_LBM_NONE                   (0 << 6)    // No Loopback
#define RCTL_LBM_PHY                    (3 << 6)    // PHY or external SerDesc loopback
#define RTCL_RDMTS_HALF                 (0 << 8)    // Free Buffer Threshold is 1/2 of RDLEN
#define RTCL_RDMTS_QUARTER              (1 << 8)    // Free Buffer Threshold is 1/4 of RDLEN
#define RTCL_RDMTS_EIGHTH               (2 << 8)    // Free Buffer Threshold is 1/8 of RDLEN
#define RCTL_MO_36                      (0 << 12)   // Multicast Offset - bits 47:36
#define RCTL_MO_35                      (1 << 12)   // Multicast Offset - bits 46:35
#define RCTL_MO_34                      (2 << 12)   // Multicast Offset - bits 45:34
#define RCTL_MO_32                      (3 << 12)   // Multicast Offset - bits 43:32
#define RCTL_BAM                        (1 << 15)   // Broadcast Accept Mode
#define RCTL_VFE                        (1 << 18)   // VLAN Filter Enable
#define RCTL_CFIEN                      (1 << 19)   // Canonical Form Indicator Enable
#define RCTL_CFI                        (1 << 20)   // Canonical Form Indicator Bit Value
#define RCTL_DPF                        (1 << 22)   // Discard Pause Frames
#define RCTL_PMCF                       (1 << 23)   // Pass MAC Control Frames
#define RCTL_SECRC                      (1 << 26)   // Strip Ethernet CRC

// Buffer Sizes
#define RCTL_BSIZE_256                  (3 << 16)
#define RCTL_BSIZE_512                  (2 << 16)
#define RCTL_BSIZE_1024                 (1 << 16)
#define RCTL_BSIZE_2048                 (0 << 16)
#define RCTL_BSIZE_4096                 ((3 << 16) | (1 << 25))
#define RCTL_BSIZE_8192                 ((2 << 16) | (1 << 25))
#define RCTL_BSIZE_16384                ((1 << 16) | (1 << 25))


// Transmit Command

#define CMD_EOP                         (1 << 0)    // End of Packet
#define CMD_IFCS                        (1 << 1)    // Insert FCS
#define CMD_IC                          (1 << 2)    // Insert Checksum
#define CMD_RS                          (1 << 3)    // Report Status
#define CMD_RPS                         (1 << 4)    // Report Packet Sent
#define CMD_VLE                         (1 << 6)    // VLAN Packet Enable
#define CMD_IDE                         (1 << 7)    // Interrupt Delay Enable


// TCTL Register

#define TCTL_EN                         (1 << 1)    // Transmit Enable
#define TCTL_PSP                        (1 << 3)    // Pad Short Packets
#define TCTL_CT_SHIFT                   4           // Collision Threshold
#define TCTL_COLD_SHIFT                 12          // Collision Distance
#define TCTL_SWXOFF                     (1 << 22)   // Software XOFF Transmission
#define TCTL_RTLC                       (1 << 24)   // Re-transmit on Late Collision

#define TSTA_DD                         (1 << 0)    // Descriptor Done
#define TSTA_EC                         (1 << 1)    // Excess Collisions
#define TSTA_LC                         (1 << 2)    // Late Collision
#define LSTA_TU                         (1 << 3)    // Transmit Underrun

//Transmit and recive buffer structures
#define E1000_NUM_RX_DESC 32
#define E1000_NUM_TX_DESC 8
struct e1000_rx_desc {
		volatile uint64_t addr;
		volatile uint16_t length;
		volatile uint16_t checksum;
		volatile uint8_t status;
		volatile uint8_t errors;
		volatile uint16_t special;
} __attribute__((packed));
struct e1000_tx_desc {
		volatile uint64_t addr;
		volatile uint16_t length;
		volatile uint8_t cso;
		volatile uint8_t cmd;
		volatile uint8_t status;
		volatile uint8_t css;
		volatile uint16_t special;
} __attribute__((packed));


/** INTEL ETHERNET i217 DRIVER END **/
#endif