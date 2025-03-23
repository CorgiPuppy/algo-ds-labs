#include <iostream>

#include "../include/GraphGenerator.h"

int main() {
	GraphGenerator generator(10, 10, 3, 20);
	Graph graph = generator.generate();

	std::cout << "Adjacency matrix:" << std::endl;
	graph.printAdjacencyMatrix();

	return 0;
}
