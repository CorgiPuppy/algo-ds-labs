#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

template <typename T>
class LinkedList {
	protected:
		int size;
		Node<T> *head;
		Node<T> *tail;

	public:
		LinkedList() : size(0), head(nullptr), tail(nullptr) {}

		void insertFront(const T &value) {
			Node<T> *newNode = new Node<T>(value);
			if (head == nullptr) {
				head = newNode;
				tail = newNode;
			} else {
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
			}
			
			size++;
		}

		bool isEmpty() const { return size == 0; }

		int getSize() const { return size; }

		class Iterator {
			private:
				Node<T> *current;

			public:
				Iterator(Node<T> *node) : current(node) {}

				T& operator*() const { return current->data; }

				Iterator& operator++() {
					if (current)
						current = current->next;

					return *this;
				}

				bool operator!=(const Iterator &other) const { return current != other.current; }
		};

		Iterator begin() const { return Iterator(head); }

		Iterator end() const { return Iterator(nullptr); }
};

#endif
