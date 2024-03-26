#include <drivers/io/ports.h>
#include <drivers/vga.h>
#include <drivers/x86/isr.h>
#include <drivers/x86/irq.h>
#include <drivers/perip/keyboard.h>
#include <shell/shell.h>
#include <system/modules.h>
#include <libssp.h>



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
			kputchar(c, COLOR_WHT, COLOR_BLK);
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
	return;
}

void input_reset() {
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
	//shell(input_buffer, i);
	memset(input_buffer, 0, sizeof(input_buffer));
	i=0;
}

void keyboard_install(){
	module_t modules_keyboard_keyboard = MODULE("kernel.modules.keyboard.keyboard", "Provides PS/2 keyboard support for the kernel (CORE)");
	char** deps;
	deps[0] = "shell";
	DEPS(modules_keyboard_keyboard, deps);
	INIT(modules_keyboard_keyboard);
	irq_install_handler(1, keyboard_handler);
	DONE(modules_keyboard_keyboard);
	 
}