#ifndef __STDIO_H
#define __STDIO_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <drivers/fs/fs.h>

#define EOF -1
#define BUFSIZ 1024

#define FILENAME_MAX 512
#define STREAM_MAX 8

//the file structure
typedef struct {
	char* name;
	char* mode;
	bool locked;
	char* lockedBy;
	long* position;
	uint8_t* stream;
	fs_node_t* node;
} FILE;

//file position structure
typedef struct {
	FILE *file;
	long offset;
} fpos_t;

//clearerr implementation
void clearerr(FILE *stream);

//ctermid implementation (returns same thing irregardless of process)
char *ctermid(char *s);

//fclose implementation
int fclose(FILE *stream);

//fopen implementation (note this implementation only has R,A,W inputs for mode)
FILE *fopen(const char *filename, const char *mode);

//fdopen implementation (note this implementation only has R,A,W inputs for mode)
FILE *fdopen(fs_node_t *fd, const char *mode);

//feof implementation
int feof(FILE *stream);

//ferror implementation
int ferror(FILE *stream);

//fflush implementation
int fflush(FILE *stream);

//fgetc implementation
int fgetc(FILE *stream);

//fgetpos implementation
int fgetpos(FILE *restrict stream, fpos_t *restrict pos);

//fgets implementation
char *fgets(char *restrict s, int n, FILE *restrict stream);

//flockfile implementation
void flockfile(FILE *file);

//ftrylockfile implementation
int ftrylockfile(FILE *file);

//funlockfile implementation
void funlockfile(FILE *file);


//fmemopen implementation
//FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode);
	
//printf implementation
void printf(char *format, ...);

//puts implementation
int puts(const char *s);

#if defined(__cplusplus)
} /* extern "C" */
#endif

	
#endif