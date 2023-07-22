#pragma once
#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#include "Optional.cpp"
#include "ToolsCollection.cpp"

template <typename K, typename T>
class NodeKeyHashLinear {

	private:

		int hashKey;
		K key;
		T* value;
		Optional<NodeKeyHashLinear<K,T>> reference;

	public:

		NodeKeyHashLinear(K k,T e) {
			new (this) NodeKeyHashLinear(k, new T(e));
		}

		NodeKeyHashLinear(K k, T* e) {
			if (e != nullptr) {
				hashKey = ToolsCollection<K>::GenerateHash(k);
				key = k;
				value = e;
			}
			else {
				throw std::runtime_error("Cannot set a null pointer as node value.");
			}
			reference = Optional<NodeKeyHashLinear<K,T>>::None();
		}

		int GetHash() {
			return hashKey;
		}

		K GetKey() {
			return key;
		}

		T* GetValue() {
			return value;
		}

		void SetValue(T* v) {
			if (v != nullptr) {
				value = v;
			}
			else {
				throw std::runtime_error("Cannot set a null pointer as node element");
			}
		}

		Optional<NodeKeyHashLinear<K, T>> GetReference() {
			return reference;
		}

		void SetReference(Optional<NodeKeyHashLinear<K, T>> r) {
			reference = r;
		}

		void SetReference(NodeKeyHashLinear<K, T> r) {
			reference = Optional<NodeKeyHashLinear<K, T>>::Some(&r);
		}

		~NodeKeyHashLinear() {
			delete value;
		}

};