#ifndef __STDIO_H
#define __STDIO_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <drivers/fs/fs.h>
#include <system/types.h>

#define EOF -1
#define BUFSIZ 1024

#define FILENAME_MAX 512
#define STREAM_MAX 8
	
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

//the file structure
typedef struct {
	int eof;
	int error;
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

//freopen implementation
FILE *freopen(const char *restrict pathname, const char *restrict mode, FILE *restrict stream);

//fscanf implementation
int fscanf(FILE *restrict stream, const char *restrict format, ...);
	
//fseek implementation
int fseek(FILE *stream, long offset, int whence);

//fseeko implementation
int fseeko(FILE *stream, off_t offset, int whence);

//fsetpos implementation
int fsetpos(FILE *stream, const fpos_t *pos);

//ftell implementation
long ftell(FILE *stream);

//ftello implementation
off_t ftello(FILE *stream);
	
//ftrylockfile implementation
int ftrylockfile(FILE *file);

//funlockfile implementation
void funlockfile(FILE *file);

//fwrite implementation
size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);

//getc implementation
int getc(FILE *stream);

//getchar implementation
int getchar(void);

//getc_unlocked implementation
int getc_unlocked(FILE *stream);

//getchar_unlocked implementation
int getchar_unlocked(void);

//getdelim implementation
ssize_t getdelim(char **restrict lineptr, size_t *restrict n, int delimiter, FILE *restrict stream);

//getline implementation
ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);
	
//gets implementation
char *gets(char *s);

//open_memstream implementation
FILE *open_memstream(char **bufp, size_t *sizep);

	

	
//putc_unlocked implementation
int putc_unlocked(int c, FILE *stream);

//putchar_unlocked implementation
//To be added
	
//printf implementation
int printf(const char *format, ...);

//puts implementation
int puts(const char *s);

//scanf implementation
int scanf(const char *restrict format, ...);

//sscanf implementation
int sscanf(const char *restrict str, const char *restrict format, ...);


	
#if defined(__cplusplus)
} /* extern "C" */
#endif

	
#endif