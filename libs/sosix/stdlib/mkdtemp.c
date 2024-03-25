#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <drivers/fs/fs.h>

char *mkdtemp(char *temp) {
	static int numberid;
	char* buf[256];
	char* strfound = strstr(temp, "xxxxxx");
	if (strfound == NULL) {
		return NULL;
	}
	temp = rstrstr(temp, "xxxxxx");
	char* strid = itoa(numberid, buf, 10);
	strcat(temp, strid); 
	numberid++;
	create_dir_fs(temp);
	return temp;
}