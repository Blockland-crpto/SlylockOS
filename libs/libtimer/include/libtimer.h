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
  \file      timer.h
  \brief     Provides timer support to the kernel
  \details   Allows the kernel to get the seconds elapsed since the OS was loaded, sleeping, and more.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __LIBTIMER_H
#define __LIBTIMER_H

#if defined(__cplusplus)
extern "C" {
#endif
	void timer_phase(int hz);

	/**
		\brief Installs the timer
	*/
	void timer_install();
	/**
		\brief Waits `val` seconds
		\param{in} val The amount of seconds to wait
	*/
	void timer_wait(int val);

	/**
		\brief Gets the seconds elapsed since Abrid was loaded
		\returns The amount of seconds elapsed since Abrid was loaded
	*/
	int get_tracked_seconds();

	//fixed timer
	void time_sleep(int time);


#if defined(__cplusplus)
} /* extern "C" */
#endif




#endif
