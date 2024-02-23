#include <ports.h>
#include <screen.h>
#include <gui.h>
#include <isr.h>
#include <irq.h>
#include <keyboard.h>
#include <shell.h>
#include <modules.h>



#define sizeof(type) (char *)(&type+1)-(char*)(&type)

int enable_shell=0;

char *buffer="";

unsigned char ascii_values[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
	0,	/* Alt */
  ' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	'{',	/* Up Arrow */
	0,	/* Page Up */
  '-',
	'<',	/* Left Arrow */
	0,
	'>',	/* Right Arrow */
  '+',
	0,	/* 79 - End key*/
	'}',	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

char input_buffer[256];

int i = 0;

void keyboard_handler(struct regs *r){
	unsigned char scancode;

	//Read the Keyboard's data port
	scancode = in_port_byte(0x60);

	if(scancode & 0x80){
		//use Shift, Alt, CTRL keys here
	}
	else{
		char c = ascii_values[scancode];
		if(i==0 && c=='\b'){
		  //do nothing
		  //this prevents clearing the '>' character on the screen
		} else {
		  if (userinputmode > 0 && textboxactive == 0) { 
		  } else if(textboxactive == 1) {
			if (i==0 && c=='\b') {
				//do nothing
				//prevents the backspace from clearing the textbox

			} else if (i >= 33) {
				//do nothing
				//prevents the textbox from overflowing
			} else {
				putchar(c, 8, 7);
			}

		  } else {
			putchar(c, COLOR_WHT, COLOR_BLK);
			//printf("User Prog %d", userinputmode);
		  }
		  track_input(c);
		}
	}

}

char get_key(){
	unsigned char scancode;

	//Read the Keyboard's data port
	scancode = in_port_byte(0x60);
	char *buf;
	kprintf(itoa(scancode, buf, 10));
	if(scancode & 0x80){
		//use Shift, Alt, CTRL keys here
	}
	else{
		char c = ascii_values[scancode];
		return c;
	}
	return 0;

}

void track_input(char c){
		if(userinputmode == 0 && textboxactive == 0) {
		  //If user hits enter, we can execute the command
		  if(c == '\n'){
			//handle shell support here
			//parse_input(input_buffer, i);
			shell(input_buffer, i);
			memset(input_buffer, 0, sizeof(input_buffer));
			i=0;
		  }
		  //handle backspace in input string buffer
		  else if(c == '\b'){
			input_buffer[i-1]='\0';
			i--;
		  }
		  //handle the input buffer if the input is greater than 255
		  else if(i >= 255){
			input_buffer[0]='\0';
			i = 0;
		  }
		  else if(c == '\t') {
		  }
		  //add new input characters from input to string buffer
		  else{
			input_buffer[i]=c;
			i++;
		  }
		} else if(userinputmode > 0 && textboxactive == 0) {
		  //This is a patch to coordinate program responces to key input
		  if (userinputmode == HELP_APP_ID) {
			if (c == '<') {
			  //Do nothing
			} else if (c == '>') {
			  avaliable_commands(2);
			}
		  } else if(userinputmode == HELP_APP_ID_TW) {
			if (c == '<') {
			  avaliable_commands(1);
			} else if (c == '>') {
			  //Do nothing
			}
		  } else if (userinputmode == ABOUT_APP_ID) {
			  if (c == '<') {
				//Do nothing
			  } else if (c == '>') {
				about(2);
			  } else if (c == 'a') {
				about_info();
			  }
		  } else if (userinputmode == ABOUT_APP_ID_TW) {
			  if (c == '<') {
				about(1);
			  } else if (c == '>') {
				//Do nothing
			  } else if (c == 'a') {
				about_info();
			  }
		  } else if (userinputmode == ABOUT_APP_ID_TH) {
			  if (c == '\n') {
				  clear(COLOR_WHT, COLOR_BLK);
				  set_cursor_pos(0,0);
				  shell(input_buffer, i);
				  memset(input_buffer, 0, sizeof(input_buffer));
				  i=0;
				  userinputmode = 0;
			  } else if (c == 'b') {
				  about(1);
			  }
		  } else if (userinputmode == LS_APP_ID) {
			  if (c == '<') {
				//Do nothing
			  } else if (c == '>') {
				ls(16, LS_APP_ID_TW, 2);
			  } else if (c == 'a') {
				ls_info();
			  }
		  } else if (userinputmode == LS_APP_ID_TW) {
			  if (c == '<') {
				ls(0, LS_APP_ID, 1);
			  } else if (c == '>') {
				ls(32, LS_APP_ID_TH, 3);
			  } else if (c == 'a') {
				ls_info();
			  }
		  } else if (userinputmode == LS_APP_ID_TH) {
			  if (c == '<') {
				ls(16, LS_APP_ID_TW, 2);
			  } else if (c == '>') {
				//ls(48, LS_APP_ID_FR, 4);
			  } else if (c == 'a') {
				ls_info();
			  }
		  /*
		  } else if (userinputmode == LS_APP_ID_FR) {
			  if (c == '<') {
				ls(32, LS_APP_ID_TH, 3);
			  } else if (c == '>') {
				ls(64, LS_APP_ID_FV, 5);
			  } else if (c == 'a') {
				ls_info();
			  }
		  } else if (userinputmode == LS_APP_ID_FV) {
			  if (c == '<') {
				ls(48, LS_APP_ID_FR, 4);
			  } else if (c == '>') {
				//Do Nothing
			  } else if (c == 'a') {
				ls_info();
			  }
		 */
		  } else if (userinputmode == LS_APP_ID_SX)  {
			  if (c == '\n') {
				  clear(COLOR_WHT, COLOR_BLK);
				  set_cursor_pos(0,0);
				  shell(input_buffer, i);
				  memset(input_buffer, 0, sizeof(input_buffer));
				  i=0;
				  userinputmode = 0;
			  } else if (c == 'b') {
				  ls(0, LS_APP_ID, 1);
			  }
			
		  } else if (userinputmode == CAT_APP_ID) {
			  if (c == '\n') {
			      clear(COLOR_WHT, COLOR_BLK);
				  set_cursor_pos(0,0);
				  shell(input_buffer, i);
				  memset(input_buffer, 0, sizeof(input_buffer));
				  i=0;
				  userinputmode = 0;
			  } else if (c == 'a') {
				  cat_info();
			  }
		  } else if (userinputmode == CAT_APP_ID_TW) {
			  if (c == '\n') {
				  clear(COLOR_WHT, COLOR_BLK);
				  set_cursor_pos(0,0);
				  shell(input_buffer, i);
				  memset(input_buffer, 0, sizeof(input_buffer));
				  i=0;
				  userinputmode = 0;
			  }
		  }

		  if (c == '\n') {
			clear(COLOR_WHT, COLOR_BLK);
			set_cursor_pos(0,0);
			shell(input_buffer, i);
			memset(input_buffer, 0, sizeof(input_buffer));
			i=0;
			userinputmode = 0;
		  } 
		} else if (textboxactive == 1) {
		 /* 
		 if (i >= 33) {
			  timesfilled + 1;

			  for(int j = 22; j < 56; j++) {
				  putpos('#', 7, 7, j, 15);
			  }
			  set_cursor_pos(22, 15);
			  for(int r = 0; r < 33; r++) {
				  putchar(input_buffer[r + timesfilled], 8, 7);
			  }
			  putchar(c, 8, 7);
			  input_buffer[i] = c;
			  i++;
		  } 
		 */

		  if (c == '\n') {
			clear(COLOR_WHT, COLOR_BLK);
			set_cursor_pos(0,0);
			textboxactive = 0;
			textinputhandler(input_buffer, userinputmode);
			i = 0;
		  } else if(c == '\b'){
			 input_buffer[i-1]='\0';
			 i--;
		  } else {
			input_buffer[i] = c;
			i++;
		  }

		}
}

void keyboard_install(){
	module_t modules_keyboard_keyboard = MODULE("kernel.modules.keyboard.keyboard", "Provides PS/2 keyboard support for the kernel (CORE)");
	char** deps;
	deps[0] = "shell";
	DEPS(modules_keyboard_keyboard, deps);
	irq_install_handler(1, keyboard_handler);
	INIT(modules_keyboard_keyboard);
}