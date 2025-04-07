#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <algorithm>
#include <random>
#include <chrono>

#include "LinkedList.h"
#include "SearchResult.h"

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

		void fillRandom(int n, int minVal = Constants::minValue, int maxVal = Constants::maxValue) {
			this->clear();
			std::random_device engine;
			std::mt19937 gen(engine());
			std::uniform_int_distribution<T> dist(minVal, maxVal);

			for (int i = 0; i < n; i++)
				this->insertEnd(dist(gen));
		}

		void fillSorted(int n) {
			this->clear();
			for (int i = 1; i <= n; i++)
				this->insertEnd(i);
		}

		template <typename TreeType>
		long long measureInsertTime(TreeType& tree) {
			auto start = std::chrono::high_resolution_clock::now();
			for (auto it = this->begin(); it != this->end(); ++it)
				tree.insert(*it);
			auto end = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		}

		template <typename TreeType>
		SearchResult measureSearchTime(TreeType& tree, int operations = Constants::amount_of_operations) {
			SearchResult result;
			if (this->isEmpty()) return result;

			DoublyLinkedList<T> searchKeys;
			std::random_device engine;
			std::mt19937 gen(engine());
			std::uniform_int_distribution<int> dist(0, this->getSize() - 1);

			auto it = this->begin();
			for (int i = 0; i < operations; i++) {
				int index = dist(gen);
				auto temp = it;
				for (int j = 0; j < index && temp != this->end(); j++)
					++temp;
				if (temp != this->end())
					searchKeys.insertEnd(*temp);
			}

			auto start = std::chrono::high_resolution_clock::now();
			for (auto key : searchKeys)
				tree.search(key);
			auto end = std::chrono::high_resolution_clock::now();

			result.totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			result.averageTime = static_cast<double>(result.totalTime) / operations;

			return result;
		}

		template <typename ListType>
		SearchResult measureListSearchTime(int operations = Constants::amount_of_operations) {
			SearchResult result;
			if (this->isEmpty()) return result;

			DoublyLinkedList<ListType> searchKeys;
			std::random_device engine;
			std::mt19937 gen(engine());
			std::uniform_int_distribution<int> dist(0, this->getSize() - 1);

			auto it = this->begin();
			for (int i = 0; i < operations; i++) {
				int index = dist(gen);
				auto temp = it;
				for (int j = 0; j < index && temp != this->end(); j++)
					++temp;
				if (temp != this->end())
					searchKeys.insertEnd(*temp);
			}
			
			auto start = std::chrono::high_resolution_clock::now();
			for (auto key : searchKeys)
				for (auto it = this->begin(); it != this->end(); ++it)
					if (*it == key) break;
			auto end = std::chrono::high_resolution_clock::now();

			result.totalTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			result.averageTime = static_cast<double>(result.totalTime) / operations;

			return result;
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
