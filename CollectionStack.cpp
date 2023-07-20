#pragma once

#include "Optional.cpp"
#include "NodeLinear.cpp"

template <typename T>
class CollectionStack {

	private:

		Optional<NodeLinear<T>> tail;

	public:

		CollectionStack() {
			tail = Optional<NodeLinear<T>>::None();
		}

		Optional<NodeLinear<T>> Get() {
			return tail;
		}

		void Insert(NodeLinear<T> child) {
			if (tail.IsNone()) {
				child.SetReference(Optional<NodeLinear<T>>::None());
			} else {
				child.SetReference(tail.Unwrap());
			}
			tail = Optional<NodeLinear<T>>::Some(&child);
		}

		Optional<NodeLinear<T>> Delete() {
			if (tail.IsSome()) {
				NodeLinear<T>* tailAux = tail.Unwrap();
				Optional<NodeLinear<T>> tailReference = tailAux->GetReference();
				Optional<NodeLinear<T>> child = Optional<NodeLinear<T>>::None();
				if (tailReference.IsSome()) {
					child = Optional<NodeLinear<T>>::Some(tailReference.Unwrap());
					tailAux->SetReference(Optional<NodeLinear<T>>::None());
				}
				tail = child;
				return Optional<NodeLinear<T>>::Some(tailAux);
			}
			return tail;
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

};
