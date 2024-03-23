#ifndef __ERRNO_H
#define __ERRNO_H

#define EDOM 2
#define EILSEQ 3
#define ERANGE 4
#define EBADF 5
#define EIO 6
#define EINVAL 7

int errno;

void errno_init();

#endif