#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <numeric>

#include "../include/Constants.h"

void insertionSort(double [], int, long long&, long long&);
void generationArray(double [], int);

int main() {
	std::ofstream worst_and_complexity(Constants::folder + "worst_and_complexity.dat");
	std::ofstream average_best_worst(Constants::folder + "average_best_worst.dat");
	std::ofstream average_swaps(Constants::folder + "average_swaps.dat");
	std::ofstream average_passes(Constants::folder + "average_passes.dat");
	if (!worst_and_complexity.is_open() ||
        !average_best_worst.is_open()   ||
        !average_swaps.is_open()        ||
        !average_passes.is_open()) {
		std::cerr << "Ошибка открытия файла!" << std::endl;
		return 1;
	}

	for (int episode = 0; episode < Constants::M; episode++) {
		int size = Constants::sizes[episode];
		double* array = new double[size];

		long double the_worst_time = 0.0;
		long double the_best_time = std::numeric_limits<long double>::max();
		long double total_time = 0.0;
		long long total_swaps = 0;
		long long total_passes = 0;

		for (int attempt = 0; attempt < Constants::amount_of_attempts - 19; attempt++) {
			long long amount_of_repeated_passes = 0;
			long long amount_of_swaps = 0;

			generationArray(array, size);
			
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

			insertionSort(array, size, amount_of_repeated_passes, amount_of_swaps);	

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
			std::cout << "Количество повторных прохождений по массиву: " << amount_of_repeated_passes << ";" << std::endl;
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

		delete [] array;
	}
	
	worst_and_complexity.close();
	average_best_worst.close();
	average_swaps.close();
	average_passes.close();

	return 0;
}

void insertionSort(double array[], int size, long long& repeated_passes, long long& swaps) {
	for (int i = 1; i < size; i++) {
		repeated_passes++;

		int j = i - 1;
		while (j > -1 && array[j] > array[j + 1]) {
			double temp = array[j];
			array[j] = array[j + 1];
			array[j + 1] = temp;

			swaps++;

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
