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
#include <libdevmgr.h>
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

	//lets validate the handler
	if (r->int_no > 256) {
		//got a weird ass interrupt number
		panic("Got a strange interrupt number", INT_ERROR);
	}
	
	//lets set the time variables so we can check for double clicking
	static int time_old;
	
	
	//lets read the 0x64 port to see if data is avalible
	uint8_t data = inb(0x64);

	//copy of data
	uint8_t data_copy = data;

	//is data avalible?
	if (((1 << 0) & data_copy)) {
		//data is avalible for read from mouse
		//lets now see if the data is from mouse
		//lets reset the data copy variable
		data_copy = data;
		
		//lets check
		if ((data_copy & (1 << 5))) {
			//it is!

			//lets make a mouse packet variable
			mouse_packet_t mouse;
			
			//lets read byte 1
			uint8_t byte1 = inb(0x60);

			//lets see if there set
			if (((1 << 0) & byte1) || ((1 << 1) & byte1 )) {
				//OSDEV.org suggests discarding the packet
				return;
			}

			//is y negative?
			if (((1 << 5) & byte1)) {
				//its negative
				mouse.negy = true;
			}

			//is x negative?
			if (((1 << 4) & byte1)) {
				//its negative
				mouse.negx = true;
			}

			//is middle button pressed?
			if (((1 << 2) & byte1)) {
				//middle button pressed
				mouse.middle_pressed = true;
				//log("Middle mouse button pressed");
			} else {
				//middle button not pressed
				mouse.middle_pressed = false;
				//log("Middle mouse button not pressed");
			}

			//is the left button pressed?
			if (((1 << 0) & byte1)) {
				//left button pressed
				//log("Left mouse button pressed");
				//lets see if its double click
				mouse.left_pressed = true;
				if (!time_old) {
					//its not double click
					mouse.double_left = false;
					time_old = get_tracked_seconds();
				} else {
					//lets see if its a double click
					if (get_tracked_seconds() < time_old+1) {
						//its a double click
						mouse.double_left = true;
						//log("left Double click");
					}
					time_old = 0;
				}
			} else {
				//left button not pressed
				mouse.left_pressed = false;
				mouse.double_left = false;
				//log("Left mouse button not pressed");
			}

			//is the right button pressed?
			if (((1 << 1) & byte1)) {
				//right button pressed
				//log("Right mouse button pressed");
				//lets see if its double click
				mouse.right_pressed = true;
				if (!time_old) {
					//its not double click
					mouse.double_right = false;
					time_old = get_tracked_seconds();
				} else {
					//lets see if its a double click
					if (get_tracked_seconds() < time_old+1) {
						//its a double click
						mouse.double_right = true;
						//log("left Double click");
					}
					time_old = 0;
				}
			} else {
				//right button not pressed
				mouse.right_pressed = false;
				mouse.double_right = false;
				//log("Right mouse button not pressed");
			}

			//lets read byte 2
			uint8_t byte2 = inb(0x60);

			//lets see the x coordinate
			if (mouse.negx) {
				//lets add the negative symbol
				uint8_t signedByte2 = byte2|0xFFFFFF00;
				
				//lets cast it
				mouse.mousex = (int)signedByte2;
			} else {
				//lets cast it
				mouse.mousex = (int)byte2;
			}
			

			//make a buffer for itoa
			//char buf[1024];
			//lets print it
			//log(itoa(mouse_x, buf, 10));

			//lets read byte 3
			uint8_t byte3 = inb(0x60);

			
			//lets cast it
			if (mouse.negy) {
				//lets change it to negative
				uint8_t signedByte3 = byte3|0xFFFFFF00;

				//lets cast it
				mouse.mousey = (int)signedByte3;
			} else {
				//cast it normally
				mouse.mousey = (int)byte3;
			}

			//lets print it
			//log(itoa(mouse_y, buf, 10));

			//now lets see if theres a forth packet
			if (mouse_id == 3 || mouse_id == 4) {
				//lets read byte 4
				uint8_t byte4 = inb(0x60);

				//lets store the z coordinate
				//TODO: see if there are more than 4 buttons
				mouse.mousez = (int)byte4;
				
			}

			//now we need to append it to the stream
			*mouse_stream = mouse;
		}
	}
}

//function to wait for the mouse
void mouse_wait(uint8_t a_type) {

	//whats our timeout?
	uint32_t timeout = 100000;

	//what is our atype?
	if (!a_type) {

		//wait for the mouse to be avalible
		while(timeout--) { // DATA
			//if the mouse is avalible
			if((inb(0x64) & 1)) {
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
			if (!(inb(0x64) & 2)) {
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