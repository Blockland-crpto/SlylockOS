#include <drivers/vga.h>
#include <libtui.h>
#include <drivers/perip/keybrd.h>
#include <string.h>
#include <slibaries/shell.h>
#include <stdio.h>
#include <stdbool.h>
#include <drivers/perip/timer.h>
#include <system/kernel.h>

void calc(int uim, int selected) {
	userinputmode = uim;

	int input_y = 7;
	int button_y = 13;
	int button_animate_delay = 400000;
	
	make_tui(themeindex, themeindex, 0, 0);
	make_tui_windows("CALC", "", 3, 3, 70, 21);
	
	

	for (int x = 5; x < 41; x++) {
		putpos('#', 8, 8, x, input_y);
		putpos('#', 8, 8, x, input_y+3);
	}

	for (int y = input_y; y < input_y+3; y++) {
		putpos('#', 8, 8, 5, y);
		putpos('#', 8, 8, 40, y);
	}

	if (input_counter == 2) {
		putstrpos(calc_anwser_str, 6, input_y+2, 8, 7, 6);
		input_counter = 0;
		memset(calc_buffer, 0, sizeof(calc_buffer));
		calc_num1 = 0;
		calc_num2 = 0;
		calc_num1_negative = false;
		calc_num2_negative = false;
		calc_index = 0;
		strcpy(prev_anwser_str, calc_anwser_str);
		calc(CALC_APP_ID, 22);
	} else {
		putstrpos(calc_buffer, 6, input_y+2, 8, 7, 6);
		if (input_counter == 0) {
			if (calc_num1_negative) {
				
				putpos('-', 8, 7, 38, input_y+2);
			}
		} else if (input_counter == 1) {
			if (calc_num2_negative) {
				putpos('-', 8, 7, 38, input_y+2);
			}
		}
	}

	//the recent anwsers column
	for (int x = 52; x < 69; x++) {
		putpos('#', 8, 8, x, input_y);
		putpos('#', 8, 8, x, input_y+3);
	}

	for (int y = input_y; y < input_y+3; y++) {
		putpos('#', 8, 8, 52, y);
		putpos('#', 8, 8, 68, y);
	}

	putstrpos("Recent Anwsers:", 52, input_y+1, 8, 7, 53);
	set_cursor_pos(53,input_y+2);
	if (negative_num == true) {
		printf("-%s", prev_anwser_str);
	} else {
		printf("%s", prev_anwser_str);
	}
	

	button("0", 8, button_y, 2, 2, false);
	button("1", 12, button_y, 2, 2, false);
	button("2", 16, button_y, 2, 2, false);
	button("3", 20, button_y, 2, 2, false);
	button("4", 24, button_y, 2, 2, false);
	button("Add", 30, button_y, 4, 2, false);
	button("Mul", 36, button_y, 4, 2, false);
	button("Clr", 42, button_y, 4, 2, false);

	button("5", 8, button_y+4, 2, 2, false);
	button("6", 12, button_y+4, 2, 2, false);
	button("7", 16, button_y+4, 2, 2, false);
	button("8", 20, button_y+4, 2, 2, false);
	button("9", 24, button_y+4, 2, 2, false);
	button("Sub", 30, button_y+4, 4, 2, false);
	button("Div", 36, button_y+4, 4, 2, false);
	button("Neg", 42, button_y+4, 4, 2, false);
	

	if (selected == 0) {
		if (calc_index < 32) {
			button("0", 8, button_y, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '0';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 1) {
		if (calc_index < 32) {
			button("1", 12, button_y, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '1';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}

	} else if (selected == 2) {
		if (calc_index < 32) {
			button("2", 16, button_y, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '2';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 3) {
		if (calc_index < 32) {
			button("3", 20, button_y, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '3';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 4) {
		if (calc_index < 32) {
			button("4", 24, button_y, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '4';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 5) {
		if (calc_index < 32) {
			button("5", 8, button_y+4, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '5';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 6) {
		if (calc_index < 32) {
			button("6", 12, button_y+4, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '6';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 7) {
		if (calc_index < 32) {
			button("7", 16, button_y+4, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '7';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 8) {
		if (calc_index < 32) {
			button("8", 20, button_y+4, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '8';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 9) {
		if (calc_index < 32) {
			button("9", 24, button_y+4, 2, 2, true);
			time_sleep(button_animate_delay);
			calc_buffer[calc_index] = '9';
			calc_index++;
			calc(CALC_APP_ID, 22);
		}
	} else if (selected == 10) {
		button("Add", 30, button_y, 4, 2, true);
		time_sleep(button_animate_delay);
		calc_num1 = atoi(calc_buffer);
		calc_op = "add";
		memset(calc_buffer, 0, sizeof(calc_buffer));
		calc_index = 0;
		calc(CALC_APP_ID, 22);
	} else if (selected == 11) {
		button("Mul", 36, button_y, 4, 2, true);
		time_sleep(button_animate_delay);
		calc_num1 = atoi(calc_buffer);
		calc_op = "mul";
		memset(calc_buffer, 0, sizeof(calc_buffer));
		input_counter = 1;
		calc_index = 0;
		calc(CALC_APP_ID, 22);
	} else if (selected == 12) {
		button("Sub", 30, button_y+4, 4, 2, true);
		time_sleep(button_animate_delay);
		calc_num1 = atoi(calc_buffer);
		memset(calc_buffer, 0, sizeof(calc_buffer));
		calc_op = "sub";
		input_counter = 1;
		calc_index = 0;
		calc(CALC_APP_ID, 22);
	} else if (selected == 13) {
		button("Div", 36, button_y+4, 4, 2, true);
		time_sleep(button_animate_delay);
		calc_num1 = atoi(calc_buffer);
		memset(calc_buffer, 0, sizeof(calc_buffer));
		calc_op = "div";
		input_counter = 1;
		calc_index = 0;
		calc(CALC_APP_ID, 22);
	} else if (selected == 14) {
		button("Clr", 42, button_y, 4, 2, true);
		time_sleep(button_animate_delay);
		if (calc_index > 0) {
			calc_index--;
			calc_buffer[calc_index] = '\0';
		}
		calc(CALC_APP_ID, 22);
	} else if (selected == 15) {
		button("Neg", 42, button_y+4, 4, 2, true);
		time_sleep(button_animate_delay);
		
		if (input_counter == 1) {
			if (calc_num2_negative == false) {
				calc_num2_negative = true;
			} else {
				calc_num2_negative = false;
			}		
		} else if (input_counter == 0) {
			if (calc_num1_negative == false) {
				calc_num1_negative = true;
			} else {
				calc_num1_negative = false;
			}
		} else {
			warning_box("Calculator Error", "Error: negative cannot be used while input-counter is 2");
		}
		calc(CALC_APP_ID, 22);
	} else if (selected == 16) {
			calc_num2 = atoi(calc_buffer);
			memset(calc_buffer, 0, sizeof(calc_buffer));
			calc_index = 0;
			input_counter = 2;

		
			if (strcmp(calc_op, "add") == 0) {
				if (calc_num1_negative == 1) {
					calc_num1 = -calc_num1;
				}

				if (calc_num2_negative == 1) {
					calc_num2 = -calc_num2;
				}	

				int temp;
				temp = calc_num1 + calc_num2;
				if (temp < 0) {
					negative_num = true;
					calc_anwser = temp * -1;
				} else {
					negative_num = false;
					calc_anwser = temp;
				}
				
			} else if (strcmp(calc_op, "sub") == 0) {
				if (calc_num1_negative == 1) {
					calc_num1 = -calc_num1;
				}

				if (calc_num2_negative == 1) {
					calc_num2 = -calc_num2;
				}	

				int temp;
				temp = calc_num1 - calc_num2;
				if (temp < 0) {
					negative_num = true;
					calc_anwser = temp * -1;
				} else {
					negative_num = false;
					calc_anwser = temp;
				}
			} else if (strcmp(calc_op, "mul") == 0) {
				if (!calc_num2_negative && !calc_num1_negative) {
					negative_num = false;
				} else if (calc_num2_negative && calc_num1_negative) {
					negative_num = false;
				} else if (calc_num1_negative && !calc_num2_negative) {
					negative_num = true;
				} else if (calc_num2_negative && !calc_num1_negative) {
					negative_num = true;
				}
				calc_anwser = calc_num1 * calc_num2;
			} else if (strcmp(calc_op, "div") == 0) {
				if (!calc_num2_negative && !calc_num1_negative) {
					negative_num = false;
				} else if (calc_num2_negative && calc_num1_negative) {
					negative_num = false;
				} else if (calc_num1_negative && !calc_num2_negative) {
					negative_num = true;
				} else if (calc_num2_negative && !calc_num1_negative) {
					negative_num = true;
				}
				calc_anwser = calc_num1 / calc_num2;
			}

			char* buf;
			calc_anwser_str = itoa(calc_anwser, buf, 10);
			calc(CALC_APP_ID, 22);
	} else if (selected == 22) {
		return;
	}
}

void calc_init() {
	input_counter = 0;
	memset(calc_buffer, 0, sizeof(calc_buffer));
	calc_num1 = 0;
	calc_num2 = 0;
	calc_num1_negative = false;
	calc_num2_negative = false;
	calc_index = 0;
}