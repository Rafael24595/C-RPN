#pragma once

#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class ToolsCollection {

	public:

		static int GenerateHash(T k) {
			hash<T> khash;
			return khash(k);
		}

};