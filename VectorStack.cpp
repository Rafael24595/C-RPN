#pragma once

#include <string>
using namespace std;

#include "Optional.cpp"
#include "NodeLinear.cpp"
#include "ToolsCollection.cpp"

template <typename T>
class VectorStack {

	private:

		Optional<NodeLinear<T>> tail;

		void Insert(NodeLinear<T>* node) {
			if (tail.IsNone()) {
				node->SetReference(Optional<NodeLinear<T>>::None());
			}
			else {
				node->SetReference(tail.Unwrap());
			}
			tail = Optional<NodeLinear<T>>::Some(node);
		}

	public:

		VectorStack() {
			tail = Optional<NodeLinear<T>>::None();
		}

		Optional<T> Get() {
			if(tail.IsSome()) {
				return Optional<T>::Some(tail.Unwrap()->GetValue());
			}
			return Optional<T>::None();
		}

		void Insert(T element) {
			NodeLinear<T>* node = new NodeLinear<T>(element);
			Insert(node);
		}

		void Insert(T* element) {
			NodeLinear<T>* node = new NodeLinear<T>(element);
			Insert(node);
		}

		Optional<T> Remove() {
			if (tail.IsSome()) {
				NodeLinear<T>* tailOriginal = tail.Unwrap();
				Optional<NodeLinear<T>> tailReference = tailOriginal->GetReference();
				tailOriginal->SetReference(Optional<NodeLinear<T>>::None());
				tail = tailReference;
				return Optional<T>::Some(tailOriginal->GetValue());
			}
			return Optional<T>::None();
		}

		int Length() {
			int count = 0;
			if (IsEmpty()) {
				return count;
			}

			Optional<NodeLinear<T>> child = tail.Unwrap();
			while (child.IsSome()) {
				child = child.Unwrap()->GetReference();
				count = count+1;
			}

			return count;
		}

		bool IsEmpty() {
			return tail.IsNone();
		}

		string ToString() {
			string str = "";
			if (IsEmpty()) {
				return str;
			}

			Optional<NodeLinear<T>> child = tail.Unwrap();
			while (child.IsSome()) {
				T value = *child.Unwrap()->GetValue();
				str = str + ToolsCollection<T>::ToString(value);
				child = child.Unwrap()->GetReference();
			}

			return str;
		}

};