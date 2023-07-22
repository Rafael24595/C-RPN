#pragma once

#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#include "Optional.cpp"
#include "NodeHashKeyLinear.cpp"

template <typename K, typename T>
class CollectionHashKey {

	private:

		Optional<NodeHashKeyLinear<K,T>> head;

		void Insert(NodeHashKeyLinear<K,T>* node) {
			node->SetReference(Optional<NodeHashKeyLinear<K,T>>::None());
			Optional<NodeHashKeyLinear<K,T>> oNode = Optional<NodeHashKeyLinear<K,T>>::Some(node);
			if (head.IsNone()) {
				head = oNode;
			}
			else {
				NodeHashKeyLinear<K, T>* previous = head.Unwrap();
				while (previous->GetReference().IsSome() && oNode.Unwrap()->GetHashKey() > previous->GetHashKey()) {
					previous = previous->GetReference().Unwrap();
				}
				Optional<NodeHashKeyLinear<K, T>> next = previous->GetReference();
				oNode.Unwrap()->SetReference(next);
				previous->SetReference(oNode);
			}
		}

	public:

		CollectionHashKey() {
			head = Optional<NodeHashKeyLinear<K,T>>::None();
		}

		Optional<T> Get(K key) {
			hash<K> khash;
			int hashKey = khash(key);
			Optional<NodeHashKeyLinear<K, T>> node = head;
			while (node.IsSome() && node.Unwrap()->GetHashKey() != hashKey) {
				node = node.Unwrap()->GetReference();
			}
			if (node.IsSome()) {
				return Optional<T>::Some(node.Unwrap()->GetElement());
			}
			return Optional<T>::None();
		}

		void Insert(K key, T element) {
			NodeHashKeyLinear<K,T>* node = new NodeHashKeyLinear<K,T>(key, element);
			Insert(node);
		}

		void Insert(K key, T* element) {
			NodeHashKeyLinear<K,T>* node = new NodeHashKeyLinear<K,T>(key, element);
			Insert(node);
		}

		Optional<T> Delete(K key) {
			hash<K> khash;
			int hashKey = khash(key);
			Optional<NodeHashKeyLinear<K, T>> node = head;
			Optional<NodeHashKeyLinear<K, T>> previous = Optional<NodeHashKeyLinear<K, T>>::None();
			while (node.IsSome() && node.Unwrap()->GetHashKey() != hashKey) {
				previous = node;
				node = node.Unwrap()->GetReference();
			}
			if (node.IsSome()) {
				Optional<NodeHashKeyLinear<K, T>> reference = node.Unwrap()->GetReference();
				previous.Unwrap()->SetReference(reference);
				node.Unwrap()->SetReference(Optional<NodeHashKeyLinear<K, T>>::None());
				return Optional<T>::Some(node.Unwrap()->GetElement());
			}

			return Optional<T>::None();
		}

		int Length() {
			int count = 0;
			if (IsEmpty()) {
				return count;
			}

			Optional<NodeHashKeyLinear<K, T>> child = head.Unwrap();
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