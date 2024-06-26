/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
/**
  \file      screen.h
  \brief     Provides screen output to the kernel
  \details   Allows the kernel to printf, kprintf, etc.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __LIBVGA_H
#define __LIBVGA_H

#include <stdint.h>
#include <stdbool.h>

/**
	\def VGA_START
	\brief VGA start address
*/
#define VGA_START 0xb8000 //VGA start address
/**
	\def VGA_WIDTH
	\brief VGA width
*/
#define VGA_WIDTH 80 //these are max coloumns in VGA
/**
	\def VGA_HEIGHT
	\brief VGA height
*/
#define VGA_HEIGHT 25 //these are max rows in VGA
/**
	\def VGA_EXTENT
	\brief VGA extent
*/
#define VGA_EXTENT 80*25

//defining available colors
#define COLOR_BLK 0     // Black
#define COLOR_BLU 1     // Blue
#define COLOR_GRN 2     // Green
#define COLOR_CYN 3     // Cyan
#define COLOR_RED 4     // Red
#define COLOR_PRP 5     // Purple
#define COLOR_BRN 6     // Brown
#define COLOR_GRY 7     // Gray
#define COLOR_DGY 8     // Dark Gray
#define COLOR_LBU 9     // Light Blue
#define COLOR_LGR 10    // Light Green
#define COLOR_LCY 11    // Light Cyan
#define COLOR_LRD 12    // Light Red
#define COLOR_LPP 13    // Light Purple
#define COLOR_YEL 14    // Yellow
#define COLOR_WHT 15    // White


//I/O ports which map the screen cursor position can be queried
//from port 0x3d4 with value 14 to request the cursor position high byte
//and we also query the same port with value 15 in the low byte
//when this port is queried, the result is saved in 0x3d5

//cursor ports:
//command port = 0x3d4 query the cursor position here
//data port = 0x3d5 read from here
/**
	\def CURSOR_PORT_COMMAND
	\brief 0x3d4 Query the cursor position here
*/
#define CURSOR_PORT_COMMAND (unsigned short) 0x3d4
/**
	\def CURSOR_PORT_DATA
	\brief 0x3d5 Read from here
*/
#define CURSOR_PORT_DATA (unsigned short) 0x3d5



// the cursor modes
#define ADVANCE 0
#define MOVE_BACK 1

#if defined(__cplusplus)
extern "C" {
#endif

	/**
	  \struct fs_node
	  \brief VGA char typedef struct

	  Defines a single character struct with close packing.
	  This struct consists of:
	  I. char: The character of the vga_char
	  II. style: The color/style of the vga_char
	*/
	typedef struct __attribute__((packed)){
		char character;
		char style;
	} vga_char;

	/**
		\brief Applies foreground and background colors to the character
		\param{in} fg_color Foreground color
		\param{in} bg_color Background color
	*/
	unsigned char vga_color(const unsigned char fg_color, const unsigned char bg_color);

	/**
		\brief Clears the window or screen with a color replacement
		\param{in} fg_color Foreground color
		\param{in} bg_color Background color
	*/
	void clear(const unsigned char fg_color, const unsigned char bg_color);

	/**
		\brief Prints a character to the screen
		\param{in} character The character to print
		\param{in} fg_color Foreground color
		\param{in} bg_color Background color
	*/
	void kputchar(const char character, const unsigned char fg_color, const unsigned char bg_color);

	/**
		\brief Prints a string to the screen
		\param{in} string The string to print
		\param{in} fg_color Foreground color
		\param{in} bg_color Background color
	*/
	void putstr(const char *string, const unsigned char fg_color, const unsigned char bg_color);

	/**
		\brief Gets the cursor position
	*/
	unsigned short get_cursor_pos();

	/**
		\brief Shows the cursor
	*/
	void show_cursor();
	/**
		\brief Hides the cursor
	*/
	void hide_cursor();

	/**
		\brief Advances the cursor
	*/
	void advance_cursor(int mode);

	/**
		\brief Sets the cursor position
		\param{in} x X coordinate of the cursor position to set
		\param{in} y Y coordinate of the cursor position to set
	*/
	void set_cursor_pos(unsigned char x, unsigned char y);

	/**
		\brief Prints a character

		Prints a character with the foreground being white and the background being black.
		\param{in} ch Character to print
	*/
	void kprintc(const char ch);
	/**
		\brief Prints a string

		Prints a string with the foreground being white and the background being black.
		\param{in} string String to print
	*/
	void kprintf(const char *string);
	/**
		\brief Puts a character at a position

		Puts a character at position (x,y) with the foreground being forecolour and the background being backcolour.
		\param{in} c Character to print
		\param{in} forecolour Foreground color
		\param{in} backcolour Background color
		\param{in} x X position of character
		\param{in} y Y position of character
	*/
	void putpos(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y);


	void color_screen(int fg, int bg);

	/**
		\brief Scrolls 1 line.
	*/
	void scroll_line();

	//put a string with a specific location
	void putstrpos(const char *string, unsigned char x, unsigned char y, unsigned char fg_color, unsigned char bg_color, int start);

	enum video_type {
		VIDEO_TYPE_NONE = 0x00,
		VIDEO_TYPE_COLOR = 0x20,
		VIDEO_TYPE_MONOCHROME = 0x30,
	};

	uint16_t detect_bios_area_hardware();

	enum video_type get_bios_area_video_type();

	void vga_init();

#if defined(__cplusplus)
} /* extern "C" */
#endif




#endif