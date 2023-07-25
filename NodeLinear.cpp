#pragma once

#include <stdexcept>

#include "Optional.cpp"

template <typename T>
class NodeLinear {

	private:

		T* value;
		Optional<NodeLinear<T>> reference;

	public:

		NodeLinear(T e) {
			new (this) NodeLinear(new T(e));
		}

		NodeLinear(T* e) {
			if (e != nullptr) {
				value = e;
			} else {
				throw std::runtime_error("Cannot set a null pointer as node value.");
			}
			reference = Optional<NodeLinear<T>>::None();
		}

		T* GetValue() {
			return value;
		}

		void SetValue(T* e) {
			if (e != nullptr) {
				value = e;
			} else {
				throw std::runtime_error("Cannot set a null pointer as node value");
			}
		}

		Optional<NodeLinear<T>> GetReference() {
			return reference;
		}

		void SetReference(Optional<NodeLinear<T>> r) {
			reference = r;
		}

		void SetReference(NodeLinear<T> r) {
			reference = Optional<NodeLinear<T>>::Some(&r);
		}

		~NodeLinear() {
			delete value;
		}

};