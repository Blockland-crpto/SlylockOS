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
#include <bitset.hpp>


template<size_t N> std::bitset<N> bitset() noexcept {
	// return a bitset thats 0
	std::bitset<N> result;
	result.val = 0;
	return result;
}

template<size_t N> std::bitset<N> bitset(unsigned long long val) noexcept {
	//return a bitset that is the value
	std::bitset<N> result;
	result.val = val;
	return result;
	
}

template<size_t N> constexpr std::bitset<N> operator&(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
	return (lhs.val &= rhs.val);
}

template<size_t N> constexpr std::bitset<N> operator|(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
	return (lhs.val |= rhs.val);
}

template<size_t N> constexpr std::bitset<N> operator^(const std::bitset<N>& lhs, const std::bitset<N>& rhs) {
	return (lhs.val ^= rhs.val);
}