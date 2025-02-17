#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <numeric>

#include "../include/Constants.h"

void insertionSort(double [], int, int&, int&);
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

	for (int episode = 0; episode < Constants::M - 5; episode++) {
		int size = Constants::sizes[episode];
		double* array = new double[size];

		double the_worst_time = 0.0;
		double the_best_time = std::numeric_limits<double>::max();
		double total_time = 0.0;
		int total_swaps = 0;
		int total_passes = 0;

		for (int attempt = 0; attempt < Constants::amount_of_attempts; attempt++) {
			int amount_of_repeated_passes = 0;
			int amount_of_swaps = 0;

			generationArray(array, size);
			
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

			insertionSort(array, size, amount_of_repeated_passes, amount_of_swaps);	

			std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> milli_diff = end - start;

			double time_taken = milli_diff.count();
			if (time_taken > the_worst_time)
				the_worst_time = time_taken;
			if (time_taken < the_worst_time)
				the_best_time = time_taken;

			total_time += time_taken;
			total_swaps += amount_of_swaps;
			total_passes += amount_of_repeated_passes;

			std::cout << std::endl << "Time: " << time_taken << " micro sec." << std::endl;
			std::cout << "Количество повторных прохождений по массиву: " << amount_of_repeated_passes << ";" << std::endl;
			std::cout << "Количество выполнения операций обмена значений: " << amount_of_swaps << "." << std::endl;
		}
	
		double average_time = total_time / Constants::amount_of_attempts;
		double average_swaps_count = static_cast<double>(total_swaps) / Constants::amount_of_attempts;
		double average_passes_count = static_cast<double>(total_passes) / Constants::amount_of_attempts;

		worst_and_complexity << size << " " << the_worst_time << " " << Constants::c * (size * size) << std::endl;
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

void insertionSort(double array[], int size, int& repeated_passes, int& swaps) {
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
