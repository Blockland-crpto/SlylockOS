#include <string.h>
#include <signal.h>
#include <libssp.h>

char *strsignal(int signum) {
	switch (signum) {
		case SIGABRT:
			return "Process abort signal.";
		case SIGFPE:
			return "Erroneous arithmetic operation.";
		case SIGILL:
			return "Illegal instruction.";
		case SIGINT:
			return "Terminal Interrupt signal.";
		case SIGSEGV:
			return "Invalid memory reference.";
		case SIGTERM:
			return "Termination signal.";
	}
}