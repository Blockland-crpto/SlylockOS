#include <stdlib.h>
 

int atexit(void (*func)(void)) {
	static int registeredFunctions;
	runAtExit[registeredFunctions] = func;
	return 0;
}