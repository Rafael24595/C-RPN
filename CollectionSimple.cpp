#pragma once

#include "ToolsCollection.cpp"
#include "Optional.cpp"
#include "NodeKeyHashLinear.cpp"

template <typename K, typename T>
class CollectionSimple {

	private:

		Optional<NodeKeyHashLinear<K,T>> head;

		void Put(NodeKeyHashLinear<K,T>* node) {
			node->SetReference(Optional<NodeKeyHashLinear<K,T>>::None());
			Optional<NodeKeyHashLinear<K,T>> oNode = Optional<NodeKeyHashLinear<K,T>>::Some(node);
			if (head.IsNone()) {
				head = oNode;
			}
			else {
				Inject(oNode);
			}
		}

		void Inject(Optional<NodeKeyHashLinear<K, T>> node) {
			Optional<NodeKeyHashLinear<K, T>> exists = FindNode(node.Unwrap()->GetKey());
			if (exists.IsSome()) {
				T* value = node.Unwrap()->GetValue();
				exists.Unwrap()->SetValue(value);
			}
			else {
				InjectOrder(node);
			}
		}

		void InjectOrder(Optional<NodeKeyHashLinear<K, T>> node) {
			NodeKeyHashLinear<K, T>* actual = head.Unwrap();
			while (actual->GetReference().IsSome() && node.Unwrap()->GetHash() < actual->GetHash()) {
				actual = actual->GetReference().Unwrap();
			}
			Optional<NodeKeyHashLinear<K, T>> next = actual->GetReference();
			node.Unwrap()->SetReference(next);
			actual->SetReference(node);
		}

		Optional<NodeKeyHashLinear<K, T>> FindNode(K key) {
			int hashKey = ToolsCollection<K>::GenerateHash(key);
			Optional<NodeKeyHashLinear<K, T>> node = head;
			while (node.IsSome() && node.Unwrap()->GetHash() != hashKey) {
				node = node.Unwrap()->GetReference();
			}
			return node;
		}

	public:

		CollectionSimple() {
			head = Optional<NodeKeyHashLinear<K,T>>::None();
		}

		Optional<T> Find(K key) {
			Optional<NodeKeyHashLinear<K, T>> node = FindNode(key);
			if (node.IsSome()) {
				return Optional<T>::Some(node.Unwrap()->GetValue());
			}
			return Optional<T>::None();
		}

		void Put(K key, T element) {
			NodeKeyHashLinear<K,T>* node = new NodeKeyHashLinear<K,T>(key, element);
			Put(node);
		}

		void Put(K key, T* element) {
			NodeKeyHashLinear<K,T>* node = new NodeKeyHashLinear<K,T>(key, element);
			Put(node);
		}

		Optional<T> Remove(K key) {
			int hashKey = ToolsCollection<K>::GenerateHash(key);
			Optional<NodeKeyHashLinear<K, T>> node = head;
			Optional<NodeKeyHashLinear<K, T>> previous = Optional<NodeKeyHashLinear<K, T>>::None();
			while (node.IsSome() && node.Unwrap()->GetHash() != hashKey) {
				previous = node;
				node = node.Unwrap()->GetReference();
			}
			if (node.IsSome()) {
				Optional<NodeKeyHashLinear<K, T>> reference = node.Unwrap()->GetReference();
				previous.Unwrap()->SetReference(reference);
				node.Unwrap()->SetReference(Optional<NodeKeyHashLinear<K, T>>::None());
				return Optional<T>::Some(node.Unwrap()->GetValue());
			}

			return Optional<T>::None();
		}

		int Size() {
			int count = 0;
			if (IsEmpty()) {
				return count;
			}

			Optional<NodeKeyHashLinear<K, T>> child = head.Unwrap();
			while (child.IsSome()) {
				child = child.Unwrap()->GetReference();
				count = count + 1;
			}

			return count;
		}

		bool IsEmpty() {
			return head.IsNone();
		}

};