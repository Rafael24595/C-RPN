#pragma once

#include <stdexcept>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#include "Optional.cpp"
#include "NodeKeyLinear.cpp"

template <typename K, typename T>
class CollectionHashKey {

	private:

		Optional<NodeKeyLinear<K,T>> head;

		void Insert(NodeKeyLinear<K,T>* node) {
			node->SetReference(Optional<NodeKeyLinear<K,T>>::None());
			Optional<NodeKeyLinear<K,T>> oNode = Optional<NodeKeyLinear<K,T>>::Some(node);
			if (head.IsNone()) {
				head = oNode;
			}
			else {
				NodeKeyLinear<K, T>* previous = head.Unwrap();
				while (previous->GetReference().IsSome() && oNode.Unwrap()->GetHashKey() > previous->GetHashKey()) {
					previous = previous->GetReference().Unwrap();
				}
				Optional<NodeKeyLinear<K, T>> next = previous->GetReference();
				oNode.Unwrap()->SetReference(next);
				previous->SetReference(oNode);
			}
		}

	public:

		CollectionHashKey() {
			head = Optional<NodeKeyLinear<K,T>>::None();
		}

		Optional<T> Get(K key) {
			hash<K> khash;
			int hashKey = khash(key);
			Optional<NodeKeyLinear<K, T>> node = head;
			while (node.IsSome() && node.Unwrap()->GetHashKey() != hashKey) {
				node = node.Unwrap()->GetReference();
			}
			if (node.IsSome()) {
				return Optional<T>::Some(node.Unwrap()->GetElement());
			}
			return Optional<T>::None();
		}

		void Insert(K key, T element) {
			NodeKeyLinear<K,T>* node = new NodeKeyLinear<K,T>(key, element);
			Insert(node);
		}

		void Insert(K key, T* element) {
			NodeKeyLinear<K,T>* node = new NodeKeyLinear<K,T>(key, element);
			Insert(node);
		}

		Optional<T> Delete(K key) {
			hash<K> khash;
			int hashKey = khash(key);
			Optional<NodeKeyLinear<K, T>> node = head;
			Optional<NodeKeyLinear<K, T>> previous = Optional<NodeKeyLinear<K, T>>::None();
			while (node.IsSome() && node.Unwrap()->GetHashKey() != hashKey) {
				previous = node;
				node = node.Unwrap()->GetReference();
			}
			if (node.IsSome()) {
				Optional<NodeKeyLinear<K, T>> reference = node.Unwrap()->GetReference();
				previous.Unwrap()->SetReference(reference);
				node.Unwrap()->SetReference(Optional<NodeKeyLinear<K, T>>::None());
				return Optional<T>::Some(node.Unwrap()->GetElement());
			}

			return Optional<T>::None();
		}

		int Length() {
			int count = 0;
			if (IsEmpty()) {
				return count;
			}

			Optional<NodeKeyLinear<K, T>> child = head.Unwrap();
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