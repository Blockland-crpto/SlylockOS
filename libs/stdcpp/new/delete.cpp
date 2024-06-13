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
#include <new.hpp>
#include <string.h>
#include <stdlib.h>
#include <libproc.h>
#include <libmem.h>
#include <libdebug.h>

void operator delete(void* ptr) noexcept {
	if (task_queue[0].entry_point == NULL) {
		//kernel called it
		kfree(ptr);
	} else {
		//userspace called it
		free(ptr);
	}
}

void operator delete(void* ptr, std::align_val_t al) noexcept {
	//lets check if this is a process or kernel doing this
	if (task_queue[0].entry_point == NULL) {
		//this is a kernel
		kfree(ptr);
	} else {
		//lets see the processes usage to ensure its used
		intptr_t ptrd = (intptr_t)ptr;
		if (ptrd % (long)al != 0) {
			//oops
			panic("delete tried to delete a wrong alignment", PROC_MEM_EXPLOIT);
		}
		free(ptr);
	}
}

void operator delete[](void* ptr, std::align_val_t al) noexcept {
	//lets check if this is a process or kernel doing this
	if (task_queue[0].entry_point == NULL) {
		//this is a kernel
		kfree(ptr);
	} else {
		//lets see the processes usage to ensure its used
		intptr_t ptrd = (intptr_t)ptr;
		if (ptrd % (long)al != 0) {
			//oops
			panic("delete tried to delete a wrong alignment", PROC_MEM_EXPLOIT);
		}
		free(ptr);
	}
}

void operator delete(void* ptr, size_t sz) noexcept {
	//lets check if this is a process or kernel doing this
	if (task_queue[0].entry_point == NULL) {
		//this is a kernel
		kfree(ptr);
	} else {
		//lets see the processes usage to ensure its used
		if (task_queue[0].memory_delegated < sz) {
			//oops
			panic("delete tried to delete over its delegated memory", PROC_MEM_EXPLOIT);
		}
		free(ptr);
	}
	
}

void operator delete [](void* ptr, size_t sz) noexcept {
	//lets check if this is a process or kernel doing this
	if (task_queue[0].entry_point == NULL) {
		//this is a kernel
		kfree(ptr);
	} else {
		//lets see the processes usage to ensure its used
		if (task_queue[0].memory_delegated < sz) {
			//oops
			panic("delete tried to delete over its delegated memory", PROC_MEM_EXPLOIT);
		}
		free(ptr);
	}
}