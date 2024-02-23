#include <string.h>

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=val;
  return dest;
}