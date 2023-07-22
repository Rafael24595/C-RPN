#pragma once

#include "Optional.cpp"
#include "NodeLinear.cpp"

template <typename T>
class CollectionQueue {

	private:

		Optional<NodeLinear<T>> head;
		Optional<NodeLinear<T>> tail;

		void Insert(NodeLinear<T>* node) {
			node->SetReference(Optional<NodeLinear<T>>::None());
			Optional<NodeLinear<T>> oNode = Optional<NodeLinear<T>>::Some(node);
			if (head.IsNone()) {
				head = oNode;
				tail = head;
			}
			else {
				tail.Unwrap()->SetReference(oNode);
				tail = oNode;
			}
		}

	public:

		CollectionQueue() {
			head = Optional<NodeLinear<T>>::None();
			tail = Optional<NodeLinear<T>>::None();
		}

		Optional<NodeLinear<T>> Get() {
			return head;
		}

		void Insert(T element) {
			NodeLinear<T>* node = new NodeLinear<T>(element);
			Insert(node);
		}

		void Insert(T* element) {
			NodeLinear<T>* node = new NodeLinear<T>(element);
			Insert(node);
		}

		Optional<NodeLinear<T>> Delete() {
			if (head.IsSome()) {
				NodeLinear<T>* headOriginal = head.Unwrap();
				Optional<NodeLinear<T>> headReference = headOriginal->GetReference();
				headOriginal->SetReference(Optional<NodeLinear<T>>::None());
				head = headReference;
				return Optional<NodeLinear<T>>::Some(headOriginal);
			}
			return head;
		}

		int Length() {
			int count = 0;
			if (IsEmpty()) {
				return count;
			}

			Optional<NodeLinear<T>> child = tail.Unwrap();
			while (child.IsSome()) {
				child = child.Unwrap()->GetReference();
				count = count + 1;
			}

			return count;
		}

		bool IsEmpty() {
			return tail.IsNone();
		}

};
