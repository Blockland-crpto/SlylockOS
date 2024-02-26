#include <slibaries/shell.h>
#include <string.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>
#include <drivers/acpi.h>
#include <drivers/cpu/cpuid.h>

void about(int page) {
  char aboutstr[220] = "MiniOS\nA Operating System written in C\nand ASM for lightweight computers.\n\nKernel Version: v1.0.0\nShell Version: v1.0.0\n\nMade Possible by:\n1. Abrid OS\n2. OSDEV.org\nThank you!\nPress Enter To Continue..."; 
  char buf;

  if (page == 1) {
	userinputmode = ABOUT_APP_ID;
	clear_scr();
	make_gui(3, 3, 1, 2);
	make_gui_windows("About OS:", aboutstr, 4, 3, 70, 22);
  } else if (page == 2) {
	 char aboutstrt[150] = "Hardware:\n\nRAM: ";
	 strcat(aboutstrt, itoa(ram_size(), buf, 10));
	 strcat(aboutstrt, "\nUptime: ");
	 strcat(aboutstrt, itoa(get_tracked_seconds(), buf, 10));
	 strcat(aboutstrt, "\nScreen Type: ");
	 if (get_bios_area_video_type() == VIDEO_TYPE_COLOR) {
		 strcat(aboutstrt, "Color\nACPI: ");
	 } else if (get_bios_area_video_type() == VIDEO_TYPE_MONOCHROME) {
		 strcat(aboutstrt, "Monochrome\nACPI: ");
	 }
	 if (acpiEnabled == 1) {
		 strcat(aboutstrt, "Enabled\nCPUID: ");
	 } else if (acpiEnabled == 0) {
		 strcat(aboutstrt, "Disabled\nCPUID: ");
	 } else if (acpiEnabled == 2) {
		 strcat(aboutstrt, "Unavaliable\nCPUID: ");
	 }
	 strcat(aboutstrt, cpu_string());
	 userinputmode = ABOUT_APP_ID_TW;
	 make_gui(3, 3, 2, 2);
	 make_gui_windows("About OS:", aboutstrt, 4, 3, 70, 22);
  }
  return 0;
}