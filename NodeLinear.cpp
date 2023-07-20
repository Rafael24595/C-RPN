#pragma once

#include <stdexcept>
#include "Optional.cpp"

template <typename T>
class NodeLinear {

	private:

		T* element;
		Optional<NodeLinear<T>> reference;

	public:

		NodeLinear(T* e) {
			element = e;
			reference = Optional<NodeLinear<T>>::None();
		}

		T* GetElement() {
			return element;
		}

		void SetElement(T* e) {
			element = e;
		}

		Optional<NodeLinear<T>> GetReference() {
			return reference;
		}

		void SetReference(Optional<NodeLinear<T>> r) {
			reference = r;
		}

		void SetReference(NodeLinear<T>* r) {
			if (r != nullptr) {
				reference = Optional<NodeLinear<T>>::Some(r);
			}
		}

};