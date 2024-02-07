#include <string.h>
#include <memory.h>
#include <screen.h>
#define NULL ((char *)0)
#define DICT_LEN 256

static char *olds;

void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
 int compare(const char *X, const char *Y)
{
    while (*X && *Y)
    {
        if (*X != *Y) {
            return 0;
        }
 
        X++;
        Y++;
    }
 
    return (*Y == '\0');
}

char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if ((q = r = strstr(str, sub)) != NULL) {
        int len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            while (p < r)
                *q++ = *p++;
        }
        while ((*q++ = *p++) != '\0')
            continue;
    }
    return str;
}
 
// Function to implement `strstr()` function
const char* strstr(const char* X, const char* Y)
{
    while (*X != '\0')
    {
        if ((*X == *Y) && compare(X, Y)) {
            return X;
        }
        X++;
    }
 
    return NULL;
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);
 
    return buffer;
}
 
// Iterative function to implement itoa() function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32)
        return buffer;
 
    // consider absolute value of number
    int n = value;
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) 
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;
 
        n = n / base;
    }
 
    // if number is 0
    if (i == 0)
        buffer[i++] = '0';
 
    // If base is 10 and value is negative, the resulting string 
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

char* strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

char* strpbrk (const char *s, const char *accept)
{
	while (*s != '\0')
	{
		const char *a = accept;
		while (*a != '\0')
		if (*a++ == *s)
			return (char *) s;
		++s;
	}
	return NULL;
}

int strspn (const char *s, const char *accept)
{
	const char *p;
	const char *a;
	int count = 0;

	for (p = s; *p != '\0'; ++p)
	{
		for (a = accept; *a != '\0'; ++a)
			if (*p == *a)
				break;
		if (*a == '\0')
			return count;
		else
			++count;
	}
	return count;
}
const char* strchr(const char* s, int c) {
    if (s == NULL) {
        return NULL;
    }
    if ((c > 255) || (c < 0)) {
        return NULL;
    }
    int s_len;
    int i;
    s_len = strlen(s);
    for (i = 0; i < s_len; i++) {
        if ((char) c == s[i]) {
            return (const char*) &s[i];
        }
    }
    return NULL;
}
unsigned int strcspn(const char *s1, const char *s2)
{
    unsigned int len =0;

    if((s1 == NULL) || (s2 == NULL))
        return len;

    while(*s1)
    {

        if(strchr(s2,*s1))
        {
            return len;
        }
        else
        {

            s1++;

            len++;
        }
    }
    return len;
}

int *create_delim_dict(char *delim)
{
    int *d = (int*)malloc(sizeof(int)*DICT_LEN);
    memset((void*)d, 0, sizeof(int)*DICT_LEN);

    int i;
    for(i=0; i< strlen(delim); i++) {
        d[delim[i]] = 1;
    }
    return d;
}



char *strtok(char* str, const char* delim)
{
    static char* p=0;
    if(str)
        p=str;
    else if(!p)
        return 0;
    str=p+strspn(p,delim);
    p=str+strcspn(str,delim);
    if(p==str)
        return p=0;
    p = *p ? *p=0,p+1 : 0;
    return str;
}


char* strcpy(char* destination, const char* source)
{
    // return if no memory is allocated to the destination
    if (destination == NULL) {
        return NULL;
    }
 
    // take a pointer pointing to the beginning of the destination string
    char *ptr = destination;
 
    // copy the C-string pointed by source into the array
    // pointed by destination
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
 
    // include the terminating null character
    *destination = '\0';
 
    // the destination is returned by standard `strcpy()`
    return ptr;
}


int atoi(char* str)
{
    // Initialize result
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
 
    // return result.
    return res;
}
int octtodec(int n)
{
    int num = n;
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 8^0
    int base = 1;
 
    int temp = num;
    while (temp == 1) {
 
        // Extracting last digit
        int last_digit = temp % 10;
        temp = temp / 10;
 
        // Multiplying last digit with appropriate
        // base value and adding it to dec_value
        dec_value += last_digit * base;
 
        base = base * 8;
    }
 
    return dec_value;
}

// Non-standarized utility functions:

int starts_with(char* starts, char* s) {
	return strstr(s, starts) == s;
}