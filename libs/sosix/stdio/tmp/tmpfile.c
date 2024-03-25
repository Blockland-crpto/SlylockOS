#include <stdio.h>
#include <drivers/fs/fs.h>

FILE* tmpfile(void) {
	static int openfiles;
	if (openfiles == TMP_MAX) {
		return NULL;
	}
	FILE* file = (FILE*)malloc(sizeof(FILE));
	char *dir = tempnam("./tmp/", "tmp_");
	char *tmp = tmpnam(dir);
	create_file_fs(tmpnam, "", 100);
	file->name = "tmpfile";
	file->mode = 'w';
	file->bufmod = _IOFBF;
	file->node = finddir_fs(fs_root, tmp); 
	file->stream = (uint8_t*)malloc(file->node->length);
	openfiles++;
	return file;
}