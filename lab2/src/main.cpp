#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <numeric>

#include "../include/Constants.h"

void heapSort(double [], int);
void makeHeap(double [], int, int);
void generationArray(double [], int);

int main() {
	std::ofstream worst_and_complexity(Constants::folder + "worst_and_complexity.dat");
	std::ofstream average_best_worst(Constants::folder + "average_best_worst.dat");
	if (!worst_and_complexity.is_open() ||
        !average_best_worst.is_open()) {
		std::cerr << "Ошибка открытия файла!" << std::endl;
		return 1;
	}

	for (int episode = 0; episode < Constants::M; episode++) {
		int size = Constants::sizes[episode];
		double* array = new double[size];

		long double the_worst_time = 0.0;
		long double the_best_time = std::numeric_limits<long double>::max();
		long double total_time = 0.0;

		for (int attempt = 0; attempt < Constants::amount_of_attempts; attempt++) {
			long long amount_of_repeated_passes = 0;
			long long amount_of_swaps = 0;
			
			generationArray(array, size);
			
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

			heapSort(array, size);

			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<long double, std::milli> milli_diff = end - start;

			long double time_taken = milli_diff.count();
			if (time_taken > the_worst_time)
				the_worst_time = time_taken;
			if (time_taken < the_best_time)
				the_best_time = time_taken;
			
			total_time += time_taken;

			std::cout << std::endl << "Время: " << time_taken << " мс." << std::endl;
		}
		long double average_time = total_time / Constants::amount_of_attempts;
		long double complexity = Constants::c * static_cast<long double>(size) * size;

		worst_and_complexity << size << " " << the_worst_time << " " << complexity << std::endl;
		average_best_worst << size << " " << average_time << " " << the_best_time << " " << the_worst_time << std::endl;

		delete [] array;
	}

	worst_and_complexity.close();
	average_best_worst.close();

	return 0;
}

void heapSort(double array[], int size) {
	for (int i = (size / 2 - 1); i >= 0; i--)
		makeHeap(array, size, i);

	for (int i = (size - 1); i >= 0; i--) {
		double temp = array[0];
		array[0] = array[i];
		array[i] = temp;
		
		makeHeap(array, i, 0);
	}
}

void makeHeap(double array[], int size, int i) {
	int largest = i;

	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < size && array[l] > array[largest])
		largest = l;

	if (r < size && array[r] > array[largest])
		largest = r;

	if (largest != i) {
		double temp = array[largest];
		array[largest] = array[i];
		array[i] = temp;

		makeHeap(array, size, largest);
	}
}

void generationArray(double array[], int size) {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_real_distribution<double> gen(Constants::min_element, Constants::max_element);

	for (int i = 0; i < size; i++)
		array[i] = gen(engine);
}
