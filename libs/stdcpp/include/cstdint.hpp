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

// regular
#define INT8_MIN -128
#define INT16_MIN -32767-1
#define INT32_MIN -2147483647-1
#define INT64_MIN -9223372036854775807-1

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807

#define UINT8_MAX 255
#define UINT16_MAX 65535
#define UINT32_MAX 4294967295U
#define UINT64_MAX 18446744073709551615

//least
#define INT_LEAST8_MIN -127
#define INT_LEAST16_MIN -32767
#define INT_LEAST32_MIN -2147483647
#define INT_LEAST64_MIN -9223372036854775807

#define INT_LEAST8_MAX 255
#define INT_LEAST16_MAX 65535
#define INT_LEAST32_MAX 4294967295
#define INT_LEAST64_MAX 18446744073709551615

#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#define UINT_LEAST32_MAX 4294967295
#define UINT_LEAST64_MAX 18446744073709551615

// fast
#define INT_FAST8_MIN -127
#define INT_FAST16_MIN -32767
#define INT_FAST32_MIN -2147483647
#define INT_FAST64_MIN -9223372036854775807

#define INT_FAST8_MAX 255
#define INT_FAST16_MAX 65535
#define INT_FAST32_MAX 4294967295
#define INT_FAST64_MAX 18446744073709551615

#define UINT_FAST8_MAX 255
#define UINT_FAST16_MAX 65535
#define UINT_FAST32_MAX 4294967295
#define UINT_FAST64_MAX 18446744073709551615

#define INTPTR_MIN -32767
#define INTPTR_MAX 32767

#define UINTPTR_MAX 65535

#define INTMAX_MIN -9223372036854775807
#define INTMAX_MAX 9223372036854775807
#define UINTMAX_MAX 18446744073709551615

#define PTRDIFF_MIN -65535
#define PTRDIFF_MAX 65535

#define SIZE_MAX 65535

#define WCHAR_MIN -127
#define WCHAR_MAX 127

#define WINT_MIN -32767
#define WINT_MAX 32767

namespace std {
	using int8_t = char;
	using int16_t = short;
	using int32_t = int;
	using int64_t = long long;

	using uint8_t = unsigned char;
	using uint16_t = unsigned short;
	using uint32_t = unsigned int;
	using uint64_t = unsigned long long;

	using int_least8_t = int8_t;
	using int_least16_t = int16_t;
	using int_least32_t = int32_t;
	using int_least64_t = int64_t;

	using uint_least8_t = uint8_t;
	using uint_least16_t = uint16_t;
	using uint_least32_t = uint32_t;
	using uint_least64_t = uint64_t;

	using int_fast8_t = int8_t;
	using int_fast16_t = int16_t;
	using int_fast32_t = int32_t;
	using int_fast64_t = int64_t;

	using uint_fast8_t = uint8_t;
	using uint_fast16_t = uint16_t;
	using uint_fast32_t = uint32_t;
	using uint_fast64_t = uint64_t;

	using intptr_t = long int;
	using uintptr_t = unsigned long int;

	using intmax_t = long int;
	using uintmax_t = unsigned long int;
}