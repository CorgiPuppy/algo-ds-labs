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
void testBST(const std::vector<int>&, bool);
void testAVL(const std::vector<int>&, bool);
void runSearchTest(BinarySearchTree<int>&, const std::vector<int>&);
void runSearchTest(AVLTree<int>&, const std::vector<int>&);

int main() {
	for (int episode = 0; episode < Constants::amount_of_series; episode++) {
		int n = pow(2, 10 + episode);
		std::cout << "n=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

		for (int loop = 0; loop < Constants::amount_of_loops / 2; loop++) {
			std::cout << "Loop " << loop + 1 << " (random data):" << std::endl;
			std::vector<int> data = generateRandomData(n);
			testBST(data, true);
			testAVL(data, true);
		}

		for (int loop = Constants::amount_of_loops / 2; loop < Constants::amount_of_loops; loop++) {
			std::cout << std::endl << "Loop " << loop + 1 << " (sorted data): " << std::endl;
			std::vector<int> data = generateRandomData(n);
			testBST(data, true);
			testAVL(data, true);
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

void testBST(const std::vector<int>& data, bool testSearch) {
	BinarySearchTree<int> tree;

	auto insertStart = std::chrono::high_resolution_clock::now();
	for (int val : data)
		tree.insert(val);
	auto insertEnd = std::chrono::high_resolution_clock::now();
	auto insertTime = std::chrono::duration_cast<std::chrono::microseconds>(insertEnd - insertStart);
	
	std::cout << "BST: " << insertTime.count() << "mks (size: " << tree.getSize() << ")" << std::endl;

	if (testSearch)
		runSearchTest(tree, data);
}

void testAVL(const std::vector<int>& data, bool testSearch) {
	AVLTree<int> tree;

	auto insertStart = std::chrono::high_resolution_clock::now();
	for (int val : data)
		tree.insert(val);
	auto insertEnd = std::chrono::high_resolution_clock::now();
	auto insertTime = std::chrono::duration_cast<std::chrono::microseconds>(insertEnd - insertStart);
	
	std::cout << "AVL: " << insertTime.count() << "mks (size: " << tree.getSize() << ")" << std::endl;

	if (testSearch)
		runSearchTest(tree, data);
}

void runSearchTest(BinarySearchTree<int>& tree, const std::vector<int>& data) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, data.size() - 1);

	std::vector<int> searchKeys;
	for (int i = 0; i < Constants::amount_of_operations; i++)
		searchKeys.push_back(data[dist(gen)]);

	auto searchStart = std::chrono::high_resolution_clock::now();
	for (int key : searchKeys)
		tree.search(key);
	auto searchEnd = std::chrono::high_resolution_clock::now();
	auto totalSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(searchEnd - searchStart);
	double averageSearchTime = totalSearchTime.count() / 1000.0;

	std::cout << "BST Search: " << totalSearchTime.count() << "mks total, " << averageSearchTime << " mks per search" << std::endl;
}

void runSearchTest(AVLTree<int>& tree, const std::vector<int>& data) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, data.size() - 1);

	std::vector<int> searchKeys;
	for (int i = 0; i < Constants::amount_of_operations; i++)
		searchKeys.push_back(data[dist(gen)]);

	auto searchStart = std::chrono::high_resolution_clock::now();
	for (int key : searchKeys)
		tree.search(key);
	auto searchEnd = std::chrono::high_resolution_clock::now();
	auto totalSearchTime = std::chrono::duration_cast<std::chrono::microseconds>(searchEnd - searchStart);
	double averageSearchTime = totalSearchTime.count() / 1000.0;

	std::cout << "AVL Search: " << totalSearchTime.count() << "mks total, " << averageSearchTime << " mks per search" << std::endl;
}
