//
// This piece of code is an attempt of writing the fastest (without intrinsics) smallest (in number of lines) and fully portable (according to C++ standards anyway)
// program solving a task of replacing all unique (ignoring case) and non-unique chars in a string with '(' and ')' respectively and aiming for the worst case scenario
// For simplicity purposes we assume English ASCII chars
//
// References:
// 1. https://en.cppreference.com/w/cpp/compiler_support
// 2. http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0145r3.pdf
//
// by Trider
//

#include <limits>
#include <string>
#include <iostream>
#include <algorithm>

int main()
{
#if (__cplusplus >= 201703L || (defined(_MSC_VER) && _MSC_VER >= 1914) || (defined(__GNUC__) && __GNUC__ >= 7)) // see [1]
	bool onceMap[std::numeric_limits<char>::max() + uint64_t(1)] = {};
	bool twiceMap[std::numeric_limits<char>::max() + uint64_t(1)] = {};

	std::string input;
	std::getline(std::cin, input);

	std::for_each(input.begin(), input.end(), [&onceMap, &twiceMap](auto& character) { twiceMap[character] |= !(onceMap[character = std::tolower(character)] ^= true); }); // as for why this is NOT undefined behavior see [2]
	std::transform(input.begin(), input.end(), input.begin(), [&twiceMap](const auto& character) { return twiceMap[character] ? ')' : '('; });

	std::printf(input.c_str());
#endif
	return 0;
}