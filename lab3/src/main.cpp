#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <numeric>

#include "Constants.h"
#include "../include/DoublyLinkedList.h"

struct Person {
	std::string lastName;
	std::string firstName;
	std::string middleName;
	std::string birthDate;

	Person(
		const std::string &lastName,
		const std::string &firstName,
		const std::string &middleName,
		const std::string &birthDate
	) :
		lastName(lastName),
		firstName(firstName),
		middleName(middleName),
		birthDate(birthDate) {}
};

int getRandomNumber(int min, int max);
void testIntegers();
void testStrings();
std::string generateBirthDate();
int calculateAge(const std::string &);
void testPersons();
void simulation();
void insertionSort(DoublyLinkedList<double>&, long long&, long long&);
void generateList(DoublyLinkedList<double>&, int);

int main() {
	srand(time(0));

	testIntegers();
	testStrings();
	testPersons();
	simulation();

	return 0;
}

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

std::string generateBirthDate() {
	int year = getRandomNumber(Constants::min_year, Constants::max_year);
	int month = getRandomNumber(Constants::min_month, Constants::max_month);
	int day = getRandomNumber(Constants::min_day, Constants::max_day);

	return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

int calculateAge(const std::string &birthDate) {
	int birthYear = std::stoi(birthDate.substr(6, 4));
	int currentYear = 2025;
	return currentYear - birthYear;
}

void testPersons() {
	DoublyLinkedList<Person> list;
	
	for (int i = 0; i < Constants::maxPersons; i++) {
		std::string lastName = Constants::lastNames[getRandomNumber(0, Constants::lastNames.size() - 1)];
		std::string firstName = Constants::firstNames[getRandomNumber(0, Constants::firstNames.size() - 1)];
		std::string middleName = Constants::middleNames[getRandomNumber(0, Constants::middleNames.size() - 1)];
		std::string birthDate = generateBirthDate();

		list.insertEnd(Person(lastName, firstName, middleName, birthDate));
	}

	DoublyLinkedList<Person> youngList;
	DoublyLinkedList<Person> oldList;

	for (DoublyLinkedList<Person>::Iterator it = list.begin(); it != list.end(); ++it) {
		int age = calculateAge((*it).birthDate);
		if (age < 20)
			youngList.insertEnd(*it);
		else if (age > 30)
			oldList.insertEnd(*it);
	}

	int dontFit = list.getSize() - youngList.getSize() - oldList.getSize();

	std::cout << "Test: Persons" << std::endl;
    std::cout << "Total persons: " << list.getSize() << std::endl;
    std::cout << "Young (<20): " << youngList.getSize() << std::endl;
    std::cout << "Old (>30): " << oldList.getSize() << std::endl;
    std::cout << "Not filtered: " << dontFit << std::endl;
}

void simulation() {
    std::ofstream worst_and_complexity(Constants::folder + "worst_and_complexity.dat");
    std::ofstream average_best_worst(Constants::folder + "average_best_worst.dat");
    std::ofstream average_swaps(Constants::folder + "average_swaps.dat");
    std::ofstream average_passes(Constants::folder + "average_passes.dat");
    if (!worst_and_complexity.is_open() ||
        !average_best_worst.is_open()   ||
        !average_swaps.is_open()        ||
        !average_passes.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
    }

    for (int episode = 0; episode < Constants::M - 2; episode++) {
        int size = Constants::sizes[episode];
        DoublyLinkedList<double> list;

		long double the_worst_time = 0.0;
        long double the_best_time = std::numeric_limits<long double>::max();
        long double total_time = 0.0;
        long long total_swaps = 0;
        long long total_passes = 0;

        for (int attempt = 0; attempt < Constants::amount_of_attempts - 19; attempt++) {
            long long amount_of_repeated_passes = 0;
            long long amount_of_swaps = 0;

            generateList(list, size);

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            insertionSort(list, amount_of_repeated_passes, amount_of_swaps);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<long double, std::milli> milli_diff = end - start;

            long double time_taken = milli_diff.count();
            if (time_taken > the_worst_time)
                the_worst_time = time_taken;
            if (time_taken < the_best_time)
                the_best_time = time_taken;

            total_time += time_taken;
            total_swaps += amount_of_swaps;
            total_passes += amount_of_repeated_passes;

            std::cout << std::endl << "Время: " << time_taken << " мс." << std::endl;
            std::cout << "Количество повторных прохождений по списку: " << amount_of_repeated_passes << ";" << std::endl;
            std::cout << "Количество выполнения операций обмена значений: " << amount_of_swaps << "." << std::endl;
        }

        long double average_time = total_time / Constants::amount_of_attempts;
        long double average_swaps_count = static_cast<long double>(total_swaps) / Constants::amount_of_attempts;
        long double average_passes_count = static_cast<long double>(total_passes) / Constants::amount_of_attempts;
        long double complexity = Constants::c * static_cast<long double>(size) * size;

        worst_and_complexity << size << " " << the_worst_time << " " << complexity << std::endl;
        average_best_worst << size << " " << average_time << " " << the_best_time << " " << the_worst_time << std::endl;
        average_swaps << size << " " << average_swaps_count << std::endl;
        average_passes << size << " " << average_passes_count << std::endl;
    }

    worst_and_complexity.close();
    average_best_worst.close();
    average_swaps.close();
    average_passes.close();
}

void insertionSort(DoublyLinkedList<double>& list, long long& repeated_passes, long long& swaps) {
	DoublyLinkedList<double>::Iterator it = list.begin();
	++it;

	while (it != list.end()) {
		repeated_passes++;

        DoublyLinkedList<double>::Iterator current = it;
        DoublyLinkedList<double>::Iterator prev = it;
        --prev;

        while (prev != list.end() && *prev > *current) {
            std::swap(*prev, *current);
            swaps++;

            if (prev != list.begin()) {
                --prev;
                --current;
            } else {
                break;
            }
        }

        ++it;
	}
}

void generateList(DoublyLinkedList<double>& list, int size) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> gen(-1.0, 1.0);

    for (int i = 0; i < size; i++) {
        list.insertEnd(gen(engine));
    }
}
