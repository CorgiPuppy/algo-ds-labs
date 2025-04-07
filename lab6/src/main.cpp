#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

#include "../include/Constants.h"
#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"

std::vector<int> generateRandomData(int);
std::vector<int> generateSortedData(int);
void testBST(const std::vector<int>&);
void testAVL(const std::vector<int>&);

int main() {
	for (int episode = 0; episode < Constants::amount_of_series; episode++) {
		int n = pow(2, 10 + episode);
		std::cout << "n=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

		for (int loop = 0; loop < Constants::amount_of_loops / 2; loop++) {
			std::cout << "Loop " << loop + 1 << " (random): ";
			std::vector<int> data = generateRandomData(n);
			testBST(data);
			testAVL(data);
		}
	}

	return 0;
}

std::vector<int> generateRandomData(int n) {
	std::vector<int> data(n);

	std::random_device engine;
	std::mt19937 gen(engine());
	std::uniform_int_distribution<int> dist(1, 1000000);

	for (int i = 0; i < n; i++)
		data[i] = dist(gen);

	return data;
}

std::vector<int> generateSortedData(int n) {
	std::vector<int> data(n);
	
	for (int i = 0; i < n; i++)
		data[i] = i + 1;
	
	return data;
}

void testBST(const std::vector<int>& data) {
	BinarySearchTree<int> tree;

	auto start = std::chrono::high_resolution_clock::now();
	for (int val : data)
		tree.insert(val);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	std::cout << "BST: " << duration.count() << "mks (size: " << tree.getSize() << ")" << std::endl;
}

void testAVL(const std::vector<int>& data) {
	AVLTree<int> tree;

	auto start = std::chrono::high_resolution_clock::now();
	for (int val : data)
		tree.insert(val);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	std::cout << "AVL: " << duration.count() << "mks (size: " << tree.getSize() << ")" << std::endl;
}
