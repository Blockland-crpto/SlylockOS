#include <abstract.h>
#include <string.h>
#include <stddef.h>
#include <drivers/cpu/cpuid.h>
#include <libssp.h>

const char * const cpu_vendor_string() {
	const char* cpu = cpu_string();
	if (strcmp(CPUID_VENDOR_AMD, cpu) == 0) {
		return "AMD";
	} else if (strcmp(CPUID_VENDOR_AMD_OLD, cpu) == 0) {
		return "AMD Legacy";
	} else if (strcmp(CPUID_VENDOR_INTEL, cpu) == 0) {
		return "Intel";
	} else if (strcmp(CPUID_VENDOR_VIA, cpu) == 0) {
		return "VIA";
	} else if (strcmp(CPUID_VENDOR_TRANSMETA, cpu) == 0) {
		return "Transmeta";
	} else if (strcmp(CPUID_VENDOR_TRANSMETA_OLD, cpu) == 0) {
		return "Transmeta Legacy";
	} else if (strcmp(CPUID_VENDOR_CYRIX, cpu) == 0) {
		return "Cyrix";
	} else if (strcmp(CPUID_VENDOR_CENTAUR, cpu) == 0) {
		return "Centaur";
	} else if (strcmp(CPUID_VENDOR_NEXGEN, cpu) == 0) {
		return "NexGen";
	} else if (strcmp(CPUID_VENDOR_UMC, cpu) == 0) {
		return "UMC";
	} else if (strcmp(CPUID_VENDOR_SIS, cpu) == 0) {
		return "SiS";
	} else if (strcmp(CPUID_VENDOR_NSC, cpu) == 0) {
		return "NSC";
	} else if (strcmp(CPUID_VENDOR_RISE, cpu) == 0) {
		return "Rise";
	} else if (strcmp(CPUID_VENDOR_VORTEX, cpu) == 0) {
		return "Vortex";
	} else if (strcmp(CPUID_VENDOR_AO486, cpu) == 0) {
		return "Ao486";
	} else if (strcmp(CPUID_VENDOR_AO486_OLD, cpu) == 0) {
		return "Ao486 Legacy";
	} else if (strcmp(CPUID_VENDOR_ZHAOXIN, cpu) == 0) {
		return "ZhaoXin";
	} else if (strcmp(CPUID_VENDOR_HYGON, cpu) == 0) {
		return "Hygon";
	} else if (strcmp(CPUID_VENDOR_ELBRUS, cpu) == 0) {
		return "Elbrus";
	} else {
		return NULL;
	}
}