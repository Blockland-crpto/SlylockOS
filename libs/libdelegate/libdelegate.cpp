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
#include <system/types.h>
#include <libssp.h>
#include <libmem.h>
#include <libproc.h>


void delegateRequest::delegateRequest(ResourceType res, int amount, proc_control_block owner) {

	//if the resource is storage
	if (res == ResourceType::STORAGE) {
		//lets first check if the owner used there quota
		if (owner.storage_delegated + amount > 1024000) {
			//the process wants to use more storage than the kernel has delegated
			//ask the user if he/she wants to allow it
			//todo
			return;
		} else {
			//the process is allowed to use the storage
			owner.storage_delegated += amount;

			//exit
			return;
		}
	} else if (res == ResourceType::MEMORY) {
		//if the resource is memory
		
	}

	//
}