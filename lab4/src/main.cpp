#include <iostream>

#include "../include/GraphGenerator.h"

int main() {
	GraphGenerator generator(5, 10, 5, 15, 3, false);
	Graph graph = generator.generate();
	graph.printGraph();
	
	std::cout << "Количество рёбер: " << graph.getNedges() << std::endl;

	return 0;
}
