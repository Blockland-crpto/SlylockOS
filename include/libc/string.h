/**
  \file      string.h
  \brief     Provides string manipulation support to the kernel
  \details   Allows the kernel to manipulate strings.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __STRING_H
#define __STRING_H


#if defined(__cplusplus)
extern "C" {
#endif
	#include <stddef.h>
	
	static char *olds;
	
	
	char *itoa(int num, char* str, int base);
	int strlen(char s[]);
	int strcmp(char s1[], char s2[]);
	char* strcat(char* destination, const char* source);
	char *strtok(char* str, const char* delim);
	char* strcpy(char* destination, const char* source);
	const char* strstr(const char* X, const char* Y);
	int octtodec(int n);
	
	unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
	unsigned char *memset(unsigned char *dest, unsigned char val, int count);
	unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
	int memcmp(const void *s1, const void *s2, int len);
	char* strdup(const char *s);
	char* strncpy(char* destination, const char* source, size_t num);
	
	
	// Non-standarized utility functions:
	
	//Exclusive library helper functions
	void swap(char *x, char *y);
	char* reverse(char *buffer, int i, int j);
		
	/**
		\brief Gets if a string starts with another string
		\param{in} starts The string that it may/may not start with
		\param{in} s The string to get if it starts with `starts`
		\returns 1 if it starts with `starts`, 0 otherwise
	*/
	int starts_with(char* starts, char* s);
	
#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
