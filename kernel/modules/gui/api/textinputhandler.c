#include <gui.h>
#include <shell.h>
#include <keyboard.h>
#include <string.h>

void textinputhandler(char *input[], int uim) {
	//printf("%s", input);
	if (uim == CAT_APP_ID) {
		cat(input);
	} else if (uim == CALC_APP_ID) {
		calc_num1 = atoi(input);
		textbox("Enter the second number", "", CALC_APP_ID_TW);
	} else if (uim == CALC_APP_ID_TW) {
		calc_num2 = atoi(input);
		textbox("[0].add, [1].sub, [2].mult, [3].div", "", CALC_APP_ID_TH);
	} else if (uim == CALC_APP_ID_TH) {
		calc_op = atoi(input);
		calc(calc_num1, calc_num2, calc_op);
	}
	
}