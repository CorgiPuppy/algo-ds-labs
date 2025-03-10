#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include "Constants.h"
#include "../include/DoublyLinkedList.h"

int getRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}

void testIntegers() {
	DoublyLinkedList<int> list;

	int sum = 0;
	int minValue = 1001;
	int maxValue = -1001;

	for (int i = 0; i < 1000; i++) {
		int value = getRandomNumber(-1000, 1000);
		list.insertEnd(value);
		sum += value;
		
		if (value < minValue) minValue = value;
		if (value < maxValue) maxValue = value;
	}

    double average = static_cast<double>(sum) / list.getSize();

    std::cout << "Test: Integers" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Min: " << minValue << std::endl;
    std::cout << "Max: " << maxValue << std::endl;
}

void testStrings() {
	DoublyLinkedList<std::string> list;

	std::vector<std::string> strings = { "BMW", "Tesla", "Toyota", "Ford", "Honda", "Audi", "Porsche", "Hyundai", "Lamborghini", "Ferrari" };

	for (std::string &str : strings)
		list.insertEnd(str);

	std::cout << "Initial list: ";
	for (DoublyLinkedList<std::string>::Iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	list.deleteNode("Hyundai");	

	std::cout << "The list after deletion " << "Hyundai: ";
 	for (DoublyLinkedList<std::string>::Iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	list.insertAtPosition("Dodge", 4);

	std::cout << "The list after insertion " << "Dodge at the 4th position: ";
 	for (DoublyLinkedList<std::string>::Iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main() {
	srand(time(0));

	testIntegers();
	testStrings();

	DoublyLinkedList<int> list;

	list.insertFront(10);
	list.insertEnd(20);
	list.insertAtPosition(15, 1);
	list.insertAtPosition(15, 1);
	list.insertAtPosition(15, 1);

	std::cout << "List size - " << list.getSize() << std::endl;
	std::cout << "List elements: ";
	for (DoublyLinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "List size - " << list.getSize() << std::endl;
	list.deleteNode(15);

	std::cout << "List size - " << list.getSize() << std::endl;
	std::cout << "List elements after deletion: ";
	for (DoublyLinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "List size - " << list.getSize() << std::endl;
	
	return 0;
}
