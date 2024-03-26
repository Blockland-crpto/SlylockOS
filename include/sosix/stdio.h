#ifndef __STDIO_H
#define __STDIO_H


#if defined(__cplusplus)
extern "C" {
#endif

	#include <stdint.h>
	#include <stddef.h>
	#include <stdbool.h>
	#include <stdarg.h>
	#include <drivers/fs/fs.h>
	#include <system/types.h>
	
	#define BUFSIZ 1024
	
	#define L_ctermid 11
	#define L_tempnam 15

	#define _IOFBF 0
	#define _IOLBF 1
	#define _IONBF 2

	#define SEEK_SET 0
	#define SEEK_CUR 1
	#define SEEK_END 2
		
	#define FILENAME_MAX 512
	#define FOPEN_MAX 8
	#define TMP_MAX 5
	
	#define EOF -1
	
	#define P_tmpdir "tmp"
	
	#define getc(s) fgetc(s)
	#define getchar() getc(stdin)
	#define putc(c, s) fputc(c, s) 
	#define putchar(c) putc(c, stdout)
	#define putchar_unlocked(c) putc_unlocked(c, stdout) 
		
	//the file structure
	typedef struct {
		int eof;
		int error;
		int bufmod;
		char* name;
		char* mode;
		bool locked;
		size_t length;
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
	
	//fileno implementation
	fs_node_t *fileno(FILE* stream);
		
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
	
	//printf implementation
	int printf(const char *format, ...);
		
	//putc_unlocked implementation
	int putc_unlocked(int c, FILE *stream);
		
	//puts implementation
	int puts(const char *s);

	//remove implementation
	int remove(const char *path);

	//rename implementation
	int rename(const char *old, const char *newName);

	//renameat implementation
	int renameat(fs_node_t* oldfd, const char *newName);

	//rewind implementation
	void rewind(FILE *stream);

	//scanf implementation
	int scanf(const char *restrict format, ...);
	
	//setbuf implementation
	void setbuf(FILE* restrict stream, char *restrict buf);	

	//setvbuf implementation
	int setvbuf(FILE *restrict stream, char *restrict buf, int type);

	//snprintf implementation
	int snprintf(char *restrict s, size_t size, const char *restrict template, ...);

	//sprintf implementation
	int sprintf(char *restrict s, const char *restrict template, ...);

	//sscanf implementation
	int sscanf(const char *restrict str, const char *restrict format, ...);

	//tempnam implementation
	char *tempnam(const char *dir, const char *prefix);

	//tmpfile implementation
	FILE* tmpfile(void);

	//tmpnam implementation
	char *tmpnam(char *s);

	//ungetc implementation
	int ungetc(int c, FILE *stream);

	//vdprintf implementation
	int vdprintf(fs_node_t *fd, const char *format, va_list ap);

	//fprintf implementation
	int vfprintf(FILE *stream, const char *format, va_list ap);

	//vfscanf implementation
	int vfscanf(FILE *restrict stream, const char *restrict format, va_list ap);

	//vprintf implementation
	int vprintf(const char *format, va_list ap);

	//vscanf implementation
	int vscanf(const char *restrict format, va_list args);

	//vsnprintf implementation
	int vsnprintf(char *restrict s, size_t size, const char *restrict template, va_list ap);

	//vsprintf implementation
	int vsprintf(char *restrict s, const char *restrict template, va_list ap);

	//vsscanf implementation
	int vsscanf(const char *restrict str, const char *restrict format, va_list args);
	
#if defined(__cplusplus)
} /* extern "C" */
#endif

	
#endif