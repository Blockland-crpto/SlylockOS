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
  \file      modules.h
  \brief     Modular kernel support.
  \details   This header file is used to support a more modular kernel.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __LIBMODULE_H
#define __LIBMODULE_H

#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C" {
#endif

	int count;

	/**
	  \struct module_t
	  \brief Module typedef struct

	  This struct consists of:
		I. usermode: Toggles usermode
		II. enabled: Toggles if the module is enabled
		III. initialized: Toggles if the module has been initialized
		IV. name: The name of the module. Similar to a import in Java, but not backwards
		V. description: The description of the module. This description is displayed with the `man` function
		VI. dependencies: List of strings of dependencies. Each dependency's name should follow the convention established by `name`.
	*/
	typedef struct module_t {
		bool usermode;
		bool enabled;
		bool initialized;
		char* name;
		char* description;
		char** dependencies;
	} module_t;

	module_t modules[256];

	/**
		\brief Creates a module with the name `name`, and the description `description`
	*/
	module_t MODULE(char* name, char* description);

	/**
		\brief Initializes the module `module`,
		\returns int so the token overlay can work
	*/
	void INIT(module_t module);

	/**
		\brief Sets the module as failed
	*/
	void FAIL(module_t module, char* reason);

	/**
		\brief Sets the module as done
	*/
	void DONE(module_t module);
	
	/**
		\brief Disables the module `module`
	*/
	void DISABLE(module_t module);
	/**
		\brief Enables the module `module`
	*/
	void ENABLE(module_t module);

	/**
		\brief Sets dependencies of module `module` to dependencies `dependencies`
	*/
	void DEPS(module_t module, char** dependencies);

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif