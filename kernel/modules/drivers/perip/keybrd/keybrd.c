#include <drivers/io/ports.h>
#include <drivers/vga.h>
#include <libtui.h>
#include <drivers/x86/isr.h>
#include <drivers/x86/irq.h>
#include <drivers/perip/keybrd.h>
#include <shell/shell.h>
#include <system/mod.h>
#include <system/im.h>
 



#define sizeof(type) (char *)(&type+1)-(char*)(&type)

int enable_shell=0;

char *buffer="";

unsigned char ascii_values[128] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	'?',			/* 29   - Control */
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
		  if (shellinput == 1) { 
			  if (i==0 && c=='\b') {
				  //do nothing
				  //prevents the backspace from clearing the textbox

			  } else if (i==43) {
				  //do nothing prevents overflows
			  }
		  } else if (textboxactive == 0) { 
		
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
	if (shellinput == 1) {

		//This handles the shell input
		if (c == ENTER_KEY) {
			cmd(input_buffer);
			memset(input_buffer, 0, sizeof(input_buffer));
			i=0;
		} else if(c == MENU_KEY) {
			shellinput = 0;
			main_menu(1, CMD_APP_ID_TW, 1);
		} else {
			putchar(c, COLOR_WHT, COLOR_BLK);
			input_buffer[i] = c;
			i++;
		}
		
	} else if(textboxactive == 0) {
		  
		  //This is a patch to coordinate program responces to key input
		  appinput_handler(c, userinputmode);

	} else if (textboxactive == 1) {
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

void tui_reset() {
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
	//shell(input_buffer, i);
	memset(input_buffer, 0, sizeof(input_buffer));
	i=0;
	userinputmode = SHELL_APP_ID;
	tui_shell();
}

void keyboard_install(){
	module_t modules_keyboard_keyboard = MODULE("kernel.modules.keyboard.keyboard", "Provides PS/2 keyboard support for the kernel (CORE)");
	shellinput = 0;
	char** deps;
	deps[0] = "shell";
	DEPS(modules_keyboard_keyboard, deps);
	irq_install_handler(1, keyboard_handler);
	INIT(modules_keyboard_keyboard);
	 
}