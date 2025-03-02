#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <limits>
#include <cmath>

#include "../include/Constants.h"

void heapSort(double array[], int, long long&, long long&, long long&);
void makeHeap(double array[], int, int, long long&, long long&, long long&, long long&);
void generationArray(double array[], int);

int main() {
    std::ofstream worst_and_complexity(Constants::folder + "worst_and_complexity.dat");
    std::ofstream average_best_worst(Constants::folder + "average_best_worst.dat");
    std::ofstream recursion_depth(Constants::folder + "recursion_depth.dat");
    std::ofstream heap_calls(Constants::folder + "heap_calls.dat");
    std::ofstream inner_heap_ratio(Constants::folder + "inner_heap_ratio.dat");

    if (!worst_and_complexity.is_open() ||
        !average_best_worst.is_open() ||
        !recursion_depth.is_open() ||
        !heap_calls.is_open() ||
        !inner_heap_ratio.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    for (int episode = 0; episode < Constants::M; episode++) {
        int size = Constants::sizes[episode];
        double* array = new double[size];

        long double the_worst_time = 0.0;
        long double the_best_time = std::numeric_limits<long double>::max();
        long double total_time = 0.0;

        long long total_heap_calls_all = 0;
        long long total_inner_heap_calls_all = 0;
        long long max_recursion_depth_all = 0;

        long double total_recursion_depth = 0.0;
        long double best_recursion_depth = std::numeric_limits<long double>::max();
        long double worst_recursion_depth = 0.0;

        for (int attempt = 0; attempt < Constants::amount_of_attempts; attempt++) {
            long long total_heap_calls = 0;
            long long total_inner_heap_calls = 0;
            long long current_depth = 0;
            long long max_recursion_depth = 0;

            generationArray(array, size);

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

            heapSort(array, size, total_heap_calls, total_inner_heap_calls, max_recursion_depth);

            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<long double, std::milli> milli_diff = end - start;

            long double time_taken = milli_diff.count();
            if (time_taken > the_worst_time)
                the_worst_time = time_taken;
            if (time_taken < the_best_time)
                the_best_time = time_taken;

            total_time += time_taken;
            total_heap_calls_all += total_heap_calls;
            total_inner_heap_calls_all += total_inner_heap_calls;

            if (max_recursion_depth > max_recursion_depth_all)
                max_recursion_depth_all = max_recursion_depth;

            total_recursion_depth += max_recursion_depth;
            if (max_recursion_depth < best_recursion_depth)
                best_recursion_depth = max_recursion_depth;
            if (max_recursion_depth > worst_recursion_depth)
                worst_recursion_depth = max_recursion_depth;

            std::cout << "Время: " << time_taken << " мс." << std::endl;
        }

        long double average_time = total_time / Constants::amount_of_attempts;
        long double complexity = Constants::c * static_cast<long double>(size) * std::log(size);
	std::cout << complexity << std::endl;

        long double average_heap_calls = static_cast<long double>(total_heap_calls_all) / Constants::amount_of_attempts;
        long double average_inner_heap_calls = static_cast<long double>(total_inner_heap_calls_all) / Constants::amount_of_attempts;
        long double inner_heap_ratio_value = (average_inner_heap_calls / average_heap_calls) * 100.0;

        long double average_recursion_depth = total_recursion_depth / Constants::amount_of_attempts;

        worst_and_complexity << size << " " << the_worst_time << " " << complexity << std::endl;
        average_best_worst << size << " " << average_time << " " << the_best_time << " " << the_worst_time << std::endl;
        recursion_depth << size << " " << average_recursion_depth << " " << best_recursion_depth << " " << worst_recursion_depth << std::endl;
        heap_calls << size << " " << average_heap_calls << " " << average_inner_heap_calls << std::endl;
        inner_heap_ratio << size << " " << inner_heap_ratio_value << std::endl;

        delete[] array;
    }

    worst_and_complexity.close();
    average_best_worst.close();
    recursion_depth.close();
    heap_calls.close();
    inner_heap_ratio.close();

    return 0;
}

void heapSort(double array[], int size, long long& total_heap_calls, long long& total_inner_heap_calls, long long& max_recursion_depth) {
    for (int i = (size / 2 - 1); i >= 0; i--) {
        long long current_depth = 0;
        makeHeap(array, size, i, total_heap_calls, total_inner_heap_calls, current_depth, max_recursion_depth);
    }

    for (int i = (size - 1); i >= 0; i--) {
        std::swap(array[0], array[i]);
        long long current_depth = 0;
        makeHeap(array, i, 0, total_heap_calls, total_inner_heap_calls, current_depth, max_recursion_depth);
    }
}

void makeHeap(double array[], int size, int i, long long& total_heap_calls, long long& total_inner_heap_calls, long long& current_depth, long long& max_recursion_depth) {
    total_heap_calls++;
    current_depth++;

    if (current_depth > max_recursion_depth)
        max_recursion_depth = current_depth;

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && array[l] > array[largest])
        largest = l;

    if (r < size && array[r] > array[largest])
        largest = r;

    if (largest != i) {
        std::swap(array[i], array[largest]);
        makeHeap(array, size, largest, total_heap_calls, total_inner_heap_calls, current_depth, max_recursion_depth);
        total_inner_heap_calls++;
    }
}

void generationArray(double array[], int size) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<double> gen(Constants::min_element, Constants::max_element);

    for (int i = 0; i < size; i++)
        array[i] = gen(engine);
}
