#include <stdio.h>
#include <stdlib.h>
#include <libssp.h>

char* getenv(const char *name) {
	char* env;
	char* dir = "./env/";
	strcat(dir, name);
	FILE* envfile = fopen(dir, "r");
	env = envfile->stream;
	fclose(envfile);
	return env;
}