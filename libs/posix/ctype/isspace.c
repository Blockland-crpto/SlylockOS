#include <ctype.h>
 

int isspace(char c) {
	int ch = (int)c;
	return (ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v');
}
