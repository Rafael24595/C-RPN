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
			std::ostringstream ss;
			ss << value;
			return ss.str();
		}

};