#include <string.h>
#include <errno.h>
 

char *strerror(int errnum) {
	switch (errnum) {
		case 0:
			return "Success";
		case EDOM:
			return "Argument out of domain";
		case EILSEQ:
			return "Illegal byte sequence";
		case ERANGE:
			return "Out of range";
		case EBADF:
			return "Bad file descriptor";
		case EIO:
			return "I/O error";
		case EINVAL:
			return "Invalid argument";
	}
}