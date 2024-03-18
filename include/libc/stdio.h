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

FILE *stdin;   // Standard input stream
FILE *stdout;  // Standard output stream
FILE *stderr;  // Standard error stream
	
//clearerr implementation
void clearerr(FILE *stream);

//ctermid implementation (returns same thing irregardless of process)
char *ctermid(char *s);

//dprintf implementation
int dprintf(fs_node_t *fd, const char *format, ...);

//fclose implementation
int fclose(FILE *stream);

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

//fmemopen implementation
FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode);
	
//fopen implementation (note this implementation only has R,A,W inputs for mode)
FILE *fopen(const char *filename, const char *mode);

//fprintf implementation
int fprintf(FILE *stream, const char *format, ...);

//fputc implementation
int fputc(int c, FILE *stream);

//fputs implementation
int fputs(const char *restrict s, FILE *restrict stream);

//fread implementation
size_t fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
	

//ftrylockfile implementation
int ftrylockfile(FILE *file);

//funlockfile implementation
void funlockfile(FILE *file);

//printf implementation
int printf(const char *format, ...);

//puts implementation
int puts(const char *s);

#if defined(__cplusplus)
} /* extern "C" */
#endif

	
#endif