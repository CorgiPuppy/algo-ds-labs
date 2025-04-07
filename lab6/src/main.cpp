#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"

std::vector<int> generateRandomData(int);
std::vector<int> generateSortedData(int);
void testBST(const std::vector<int>&);

int main() {
	std::cout << "Hello" << std::endl;

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
}
