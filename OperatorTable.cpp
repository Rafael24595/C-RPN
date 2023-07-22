#pragma once

#include "Optional.cpp"
#include "CollectionHashKey.cpp"

class OperatorTable {

	private:
		CollectionHashKey<std::string, int>* precedence = []() {
			CollectionHashKey<std::string, int>* p = new CollectionHashKey<std::string, int>();
			p->Insert("+", 2);
			p->Insert("-", 2);
			p->Insert("/", 3);
			p->Insert("*", 3);
			p->Insert("^", 4);
			return p;
		}();

	public:

		static Optional<int> GetPrecedence(char o) {
			OperatorTable table = OperatorTable();
			string key = &o;
			return table.precedence->Get(key);
		}

};