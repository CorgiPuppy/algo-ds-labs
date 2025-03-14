#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <algorithm>

#include "LinkedList.h"

template <typename T>
class DoublyLinkedList : public LinkedList<T> {
	public:
		void insertEnd(const T& value) {
			Node<T> *newNode = new Node<T>(value);
			if (this->head == nullptr) {
				this->head = newNode;
				this->tail = newNode;
			} else {
				newNode->prev = this->tail;
				this->tail->next = newNode;
				this->tail = newNode;
			}

			this->size++;
		}

		void insertAtPosition(const T &value, int position) {
			if (position < 0 || position > this->size)
				throw std::out_of_range("The position is out of range.");

			if (position == 0)
				this->insertFront(value);
			else if (position == this->size)
				this->insertEnd(value);
			else {
				Node<T> *newNode = new Node<T>(value);
				Node<T> *current = this->head;

				for (int i = 0; i < position - 1; i++)
					current = current->next;

				newNode->next = current->next;
				newNode->prev = current;
				current->next->prev = newNode;
				current->next = newNode;

				this->size++;
			}
		}

		void deleteNode(const T &value) {
			Node<T> *current = this->head;
			while (current != nullptr) {
				if (current->data == value) {
					if (current->prev != nullptr)
						current->prev->next = current->next;
					else
						this->head = current->next;

					if (current->next != nullptr)
						current->next->prev = current->prev;
					else
						this->tail = current->prev;
					
					delete current;

					this->size--;

					break;
				}

				current = current->next;
			}
		}

		void shuffle() {
			if (this->size <= 1)
				std::cerr << "There isn't anything to shuffle!";

			std::vector<T> elements;
			for (typename DoublyLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it)
				elements.push_back(*it);

			std::random_device rd;
			std::mt19937 gen(rd());
			std::shuffle(elements.begin(), elements.end(), gen);

			this->clear();
			for (const T &element : elements)
				this->insertEnd(element);
		}

		void clear() {
			while (this->head != nullptr) {
				Node<T>* temp = this->head;
				this->head = this->head->next;
				delete temp;
			}
			this->tail = nullptr;
			this->size = 0;
		}
};

#endif
