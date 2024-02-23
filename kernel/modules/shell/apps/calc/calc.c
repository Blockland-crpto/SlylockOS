#include <screen.h>
#include <gui.h>
#include <keyboard.h>
#include <string.h>
#include <shell.h>
#include <stdio.h>

void calc(int num1, int num2, int op) {
	int result;
	char buf;
	char restr[100] = "Result: ";
	
	if (op == 0) {
		result = num1 + num2;
	} else if (op == 1) {
		result = num1 - num2;
	} else if (op == 2) {
		result = num1 * num2;
	} else if (op == 3) {
		result = num1 / num2;
	}

	strcat(restr, itoa(result, buf, 10));
	infobox("Calc", restr, CALC_APP_ID_FR, 1);
}