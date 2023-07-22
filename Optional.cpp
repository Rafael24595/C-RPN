#pragma once

#include <stdexcept>

template <typename T>
class Optional {

	private:

		T* element;

	public:

		Optional() {
			element = nullptr;
		}

		Optional(T* e) {
			element = e;
		}

		static Optional<T> None() {
			return Optional<T>(nullptr);
		}

		static Optional<T> Some(T e) {
			return Some(new T(e));
		}

		static Optional<T> Some(T* e) {
			if (e != nullptr) {
				return Optional<T>(e);
			}
			return None();
		}

		bool IsSome() {
			return element != nullptr;
		}

		bool IsNone() {
			return !IsSome();
		}

		T* Unwrap() {
			if (IsSome()) {
				return element;
			}
			throw std::runtime_error("Attempting to unwrap None Optional");
		}

};