#pragma once

#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class ToolsCollection {

	public:

		static int GenerateHash(T k) {
			hash<T> khash;
			return khash(k);
		}

		static std::string ToString(const T& value) {
			if constexpr (std::is_convertible_v<T, std::ostream>) {
				std::ostringstream ss;
				ss << value;
				return ss.str();
			}
			else {
				throw std::runtime_error("Cannot convert type T to string.");
			}
		}

};