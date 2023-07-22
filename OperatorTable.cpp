#pragma once

#include "Optional.cpp"
#include "CollectionHash.cpp"

class OperatorTable {

	private:
		CollectionHash<std::string, int>* precedence = []() {
			CollectionHash<std::string, int>* p = new CollectionHash<std::string, int>();
			p->Put("+", 2);
			p->Put("-", 2);
			p->Put("/", 3);
			p->Put("*", 3);
			p->Put("^", 4);
			return p;
		}();

	public:

		static Optional<int> GetPrecedence(char o) {
			OperatorTable table = OperatorTable();
			string key = &o;
			return table.precedence->Find(key);
		}

};