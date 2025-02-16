#include <iostream>
#include <random>
#include <chrono>

#include "../include/Constants.h"

void insertionSort(double [], int);
void generationArray(double [], int);

int main() {
//	for (int episode = 0; episode < Constants::M; episode++)
	int size = 10;
	double* array = new double[size];

	for (int attempt = 0; attempt < Constants::amount_of_attempts; attempt++) {
		generationArray(array, size);
		
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		insertionSort(array, size);	
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < size; i++) 
			std::cout << array[i] << ", ";
		std::cout << std::endl;
	}

	delete [] array;

	return 0;
}

void insertionSort(double array[], int size) {
	for (int i = 0; i < size; i++) {
		int j = i - 1;
		while (j > -1 && array[j] > array[j + 1]) {
			double temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;
			j--;
		}
	}
}

void generationArray(double array[], int size) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_real_distribution<double> gen(-1.0, 1.0);

	for (int i = 0; i < size; i++)
		array[i] = gen(engine);
}
