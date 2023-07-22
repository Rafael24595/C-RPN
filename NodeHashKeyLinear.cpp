#pragma once
#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#include "Optional.cpp"

template <typename K, typename T>
class NodeHashKeyLinear {

	private:

		int hashKey;
		K key;
		T* element;
		Optional<NodeHashKeyLinear<K,T>> reference;

	public:

		NodeHashKeyLinear(K k,T e) {
			new (this) NodeHashKeyLinear(k, new T(e));
		}

		NodeHashKeyLinear(K k, T* e) {
			if (e != nullptr) {
				hash<K> khash;
				hashKey = khash(k);
				key = k;
				element = e;
			}
			else {
				throw std::runtime_error("Cannot set a null pointer as node element");
			}
			reference = Optional<NodeHashKeyLinear<K,T>>::None();
		}

		int GetHashKey() {
			return hashKey;
		}

		K GetKey() {
			return key;
		}

		T* GetElement() {
			return element;
		}

		void SetElement(T* e) {
			if (e != nullptr) {
				element = e;
			}
			else {
				throw std::runtime_error("Cannot set a null pointer as node element");
			}
		}

		Optional<NodeHashKeyLinear<K, T>> GetReference() {
			return reference;
		}

		void SetReference(Optional<NodeHashKeyLinear<K, T>> r) {
			reference = r;
		}

		void SetReference(NodeHashKeyLinear<K, T> r) {
			reference = Optional<NodeHashKeyLinear<K, T>>::Some(&r);
		}

		~NodeHashKeyLinear() {
			delete element;
		}

};