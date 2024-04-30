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
//Contains adapted code from SANik's Mouse driver, Thank You!
#include <libmouse.h>
#include <libtimer.h>
#include <libports.h>
#include <libdebug.h>
#include <libvga.h>
#include <libdmgctrl.h>
#include <drivers/irq.h>
#include <libmodule.h>
#include <libssp.h>
#include <string.h>

//TODO:
// - Add support for mouse wheel
// - Fix button press bug
// - Add support for mouse acceleration

//the mouse_handler
void mouse_handler(struct regs *r){
	//todo: implement mouse handler
	//lets set the time variables so we can check for double clicking
	static int time_old;
	
	
	//lets read the 0x64 port to see if data is avalible
	uint8_t data = inb(0x64);

	//copy of data
	uint8_t data_copy = data;

	//is data avalible?
	if ((data_copy & (1 << 0)) == 1) {
		//data is avalible for read from mouse
		//lets now see if the data is from mouse
		//lets reset the data copy variable
		data_copy = data;
		
		//lets check
		if ((data_copy & (1 << 5)) == 1) {
			//it is!
			//lets have booleans ready
			bool y_neg;
			bool x_neg;

			//lets have mouse coordinates ready
			int mouse_x;
			int mouse_y;
			int mouse_z;
			
			//lets read byte 1
			uint8_t byte1 = inb(0x60);

			//lets see if there set
			if ((byte1 & (1 << 0)) == 1 || (byte1 & (1 << 1)) == 1) {
				//OSDEV.org suggests discarding the packet
				return;
			}

			//is y negative?
			if ((byte1 & (1 << 5)) == 1) {
				//its negative
				y_neg = true;
			}

			//is x negative?
			if ((byte1 & (1 << 4)) == 1) {
				//its negative
				x_neg = true;
			}

			//now lets see if any of the button bits set
			uint8_t mid_butn_mask = 1 << 2;
			uint8_t rgt_butn_mask = 1 << 1;
			uint8_t lft_butn_mask = 1 << 0;
			

			//is middle button pressed?
			if (byte1&mid_butn_mask) {
				//middle button pressed
				//log("Middle mouse button pressed");
			} else {
				//middle button not pressed
				//log("Middle mouse button not pressed");
			}

			//is the left button pressed?
			if (byte1&lft_butn_mask) {
				//left button pressed
				//log("Left mouse button pressed");
				//lets see if its double click
				if (time_old == 0) {
					//its not double click
					time_old = get_tracked_seconds();
				} else {
					//lets see if its a double click
					if (get_tracked_seconds() < time_old+1) {
						//its a double click
						//log("left Double click");
					}
					time_old = 0;
				}
			} else {
				//left button not pressed
				//log("Left mouse button not pressed");
			}

			//is the right button pressed?
			if (byte1&rgt_butn_mask) {
				//right button pressed
				//log("Right mouse button pressed");
				//lets see if its double click
				if (time_old == 0) {
					//its not double click
					time_old = get_tracked_seconds();
				} else {
					//lets see if its a double click
					if (get_tracked_seconds() < time_old+1) {
						//its a double click
						//log("left Double click");
					}
					time_old = 0;
				}
			} else {
				//right button not pressed
				//log("Right mouse button not pressed");
			}

			//lets read byte 2
			uint8_t byte2 = inb(0x60);

			//lets see the x coordinate
			if (x_neg) {
				//lets add the negative symbol
				uint8_t signedByte2 = byte2|0xFFFFFF00;
				
				//lets cast it
				mouse_x = (int)signedByte2;
			} else {
				//lets cast it
				mouse_x = (int)byte2;
			}
			

			//make a buffer for itoa
			char buf[1024];
			
			//lets print it
			//log(itoa(mouse_x, buf, 10));

			//lets read byte 3
			uint8_t byte3 = inb(0x60);

			
			//lets cast it
			if (y_neg) {
				//lets change it to negative
				uint8_t signedByte3 = byte3|0xFFFFFF00;

				//lets cast it
				mouse_y = (int)signedByte3;
			} else {
				//cast it normally
				mouse_y = (int)byte3;
			}

			//lets print it
			//log(itoa(mouse_y, buf, 10));

			//now lets see if theres a forth packet
			if (mouse_id == 3 || mouse_id == 4) {
				//lets read byte 4
				uint8_t byte4 = inb(0x60);

				//lets store the z coordinate
				//TODO: see if there are more than 4 buttons
				mouse_z = (int)byte4;
				
			}
		}
	}
}

//function to wait for the mouse
void mouse_wait(uint8_t a_type) {

	//whats our timeout?
	uint32_t timeout = 100000;

	//what is our atype?
	if (a_type == 0) {

		//wait for the mouse to be avalible
		while(timeout--) { // DATA
			//if the mouse is avalible
			if((inb(0x64) & 1) == 1) {
				//we have a mouse
				return;
			}
		}

		//return as its timeout is reached
		return;
	} else {
		//wait for the mouse to be avalible
		while(timeout--) { // SIGNAL
			//if the mouse is avalible
			if ((inb(0x64) & 2) == 0) {
				//we have a mouse
				return;
			}
		}

		//return as its timeout is reached
		return;
	}
}

//function to write to the mouse
void mouse_write(uint8_t data) {
	//lets wait for mouse to be ready..
	mouse_wait(1);

	//lets tell the mouse that a command is going to be sent
	outb(0x64, 0xD4);

	//more waiting...
	mouse_wait(1);

	//lets write!
	outb(0x60, data);
}

//function to read from the mouse
uint8_t mouse_read() {
	//lets wait for mouse to be ready..
	mouse_wait(0);

	//lets return the inb
	return inb(0x60);
}

//the mouse_install function
void mouse_install() {
	module_t modules_mouse = MODULE("kernel.modules.mouse", "Provides PS/2 mouse support for the kernel (CORE)");

	//let the mouse init begin!
	INIT(modules_mouse);

	//lets wait for mouse to be ready..
	mouse_wait(1);

	//lets enable the mouse using AUX command
	outb(0x64, 0xA8);

	//lets wait for mouse to be ready..
	mouse_wait(1);
	
	//lets get the status byte
	outb(0x64, 0x20);

	//lets wait for mouse to be ready..
	mouse_wait(0);
	
	//lets get the byte
	uint8_t status = inb(0x60);

	//lets mod it to enable the mouse
	status |= 1 << 1;
	status |= 0 << 5;

	//lets wait for mouse to be ready..
	mouse_wait(1);
	
	//lets send the command
	outb(0x64, 0x60);

	//lets wait for mouse to be ready..
	mouse_wait(1);

	//send the modified one
	outb(0x60, status);

	//need to tell the mouse to use default settings
	mouse_write(MOUSE_SET_DEFAULTS);

	//now we need to acknoledge it
	mouse_read();

	//last but not least we need to enable the mouse
	mouse_write(MOUSE_ENABLE_PACKET_STREAMING);

	//and acknoledge it
	mouse_read();

	//now lets get the mouse id
	mouse_write(MOUSE_GET_MOUSEID);

	//let wait and read it
	mouse_id = (int)mouse_read();
	
	//lets install the mouse handler
	irq_install_handler(12, mouse_handler);
	
	DONE(modules_mouse); 
}