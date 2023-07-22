#pragma once
#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#include "Optional.cpp"

template <typename K, typename T>
class NodeKeyLinear {

	private:

		int hashKey;
		K key;
		T* element;
		Optional<NodeKeyLinear<K,T>> reference;

	public:

		NodeKeyLinear(K k,T e) {
			new (this) NodeKeyLinear(k, new T(e));
		}

		NodeKeyLinear(K k, T* e) {
			if (e != nullptr) {
				hash<K> khash;
				hashKey = khash(k);
				key = k;
				element = e;
			}
			else {
				throw std::runtime_error("Cannot set a null pointer as node element");
			}
			reference = Optional<NodeKeyLinear<K,T>>::None();
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

		Optional<NodeKeyLinear<K, T>> GetReference() {
			return reference;
		}

		void SetReference(Optional<NodeKeyLinear<K, T>> r) {
			reference = r;
		}

		void SetReference(NodeKeyLinear<K, T> r) {
			reference = Optional<NodeKeyLinear<K, T>>::Some(&r);
		}

		~NodeKeyLinear() {
			delete element;
		}

};