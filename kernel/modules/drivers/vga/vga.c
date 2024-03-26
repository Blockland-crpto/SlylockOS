#include <drivers/io/ports.h>
#include <drivers/vga.h>
#include <stdarg.h>
#include <string.h>
#include <system/types.h>
#include <shell/shell.h>
#include <system/mod.h>
#include <drivers/perip/keybrd.h>
#include <system/debug.h>
 #include <libssp.h>


volatile vga_char *TEXT_AREA = (vga_char*) VGA_START;



void clear(unsigned char fg_color, unsigned char bg_color){
    const char space = ' ';
    unsigned char clear_color = vga_color(fg_color, bg_color); // Creates a vga color based off of the fg and bg color

    const vga_char clear_char = { // Creates a vga_char
        .character = space, // with the character being blank
        .style = clear_color // and the color being the previously defined clear_color
    };

    for(unsigned long i = 0; i < VGA_EXTENT; i++) { // Loops over the extent of the vga screen 
        TEXT_AREA[i] = clear_char; // and sets every character to the previously defined clear_char
    }
}

void kputchar(const char character, const unsigned char fg_color, const unsigned char bg_color){
    unsigned short position = get_cursor_pos(); // Get the cursor position

    if (character == '\n'){ // If the character is a newline, then set the cursor x and y to 0 and y+1 respectively. If the screen is on the last row of text, scroll
        unsigned char current_row = (unsigned char) (position / VGA_WIDTH); 

        if (++current_row >= VGA_HEIGHT){
            scroll_line();
        }
        else{
            set_cursor_pos(0, current_row);
        }
    }
    else if(character == '\b'){ // If the character is a backspace, then move the cursor position to (x-1, y), set the character to a blank character, and then move the character back again.
        advance_cursor(MOVE_BACK);
        kputchar(' ', fg_color, bg_color);
        advance_cursor(MOVE_BACK);
    }
    else if (character == '\r'){ // If the character is a carriage return, then set the cursor position to (0, pos/vga_width), usually (0, pos/80)
        unsigned char current_row = (unsigned char) (position / VGA_WIDTH);

        set_cursor_pos(0, current_row);
    }

    else if (character == '\t'){ // If the character is a tab, then turn the tab into 4 spaces and advance the cursor to the end of the 4 spaces.
        // Turn tab to 4 spaces
        for (unsigned char i = 0; i < 4; i++){
            kputchar(' ', fg_color, bg_color);
        }
        advance_cursor(ADVANCE);
    }

    else { // If the character is just a regular character, no escape character, then simply print the colored character, and advance the cursor.
        unsigned char style = vga_color(fg_color, bg_color);
        vga_char printed = {
            .character = character,
            .style = style
        };

        TEXT_AREA[position] = printed;

        advance_cursor(ADVANCE);
    }
}


void scroll_line(){
    // Moves all the lines up one
    for(unsigned short i = 1; i < VGA_HEIGHT; i++){
        for(unsigned short j = 0; j < VGA_WIDTH; j++){
            unsigned short to_pos = j + ((i - 1) * VGA_WIDTH);
            unsigned short from_pos = j + (i * VGA_WIDTH);

            TEXT_AREA[to_pos] = TEXT_AREA[from_pos];
        }
    }

    // and clears the bottommost row
    unsigned short i = VGA_HEIGHT - 1;
    for(unsigned short j = 0; j < VGA_WIDTH; j++){
        unsigned short pos = j + (i * VGA_WIDTH);

        vga_char current = TEXT_AREA[pos];
        vga_char clear = {
            .character=' ',
            .style = current.style
        };

        TEXT_AREA[pos] = clear;
    }
	// then sets the cursor y to the second-to-bottommost row
    set_cursor_pos(0, VGA_HEIGHT - 1);
}


void vga_init() {

	module_t modules_vga_vga = MODULE("kernel.modules.vga.vga", "vga drivers for the kernel (CORE)");
	if (get_bios_area_video_type() != VIDEO_TYPE_COLOR && get_bios_area_video_type() != VIDEO_TYPE_MONOCHROME) {
		panic("Unable to find screen type", VIDEO_RETRIV_ERROR);
	}
	INIT(modules_vga_vga);
	 
}