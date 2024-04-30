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
#include <libdelegate.h>
#include <libmodule.h>
#include <libproc.h>
#include <system/types.h>

#define STORAGE_DEMAND_THRESHOLD 102400
#define MEMORY_DEMAND_THRESHOLD 102400

//function to initiate the delegate
void delegate_init() {
	module_t modules_delegate = MODULE("kernel.modules.delegate", "Provides resource delegation for the kernel (CORE)");

	//let the initalization begin!
	INIT(modules_delegate);

	//were done!
	DONE(modules_delegate);
}

//function to handle delegate requests
int delegate_request(enum resource_type type, proc_control_block* proc, size_t amount) {
	//lets first check if the requesting process has used its quota'
	//lets switch!
	switch(type) {
		//if its memory
		case RESOURCE_MEMORY: {
			//has it reached its memory threshold?
			if(proc->memory_delegated + amount >= MEMORY_DEMAND_THRESHOLD) {
				//oops! we need to ask user if this is OK
				//todo:
				return 1;
			} else {
				//its okay
				proc->memory_delegated += amount; 

				//exit
				return 0;
			}
		}
		//if its a storage request
		case RESOURCE_STORAGE: {
			//has it reached its storage threshold?
			if(proc->storage_delegated + amount >= STORAGE_DEMAND_THRESHOLD) {
				//oops! we need to ask user if this is OK
				//todo:
				return 1;
			} else {
				//its okay
				proc->storage_delegated += amount;
				
				//exit
				return 0;
			}
		}
			
	}
}
