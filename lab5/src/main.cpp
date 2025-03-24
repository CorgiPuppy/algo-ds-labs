#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/GraphGenerator.h"
#include "../include/Constants.h"

int main() {
	GraphGenerator generator(Constants::minVertices, Constants::maxVertices, Constants::minEdges, Constants::maxEdges);

	Graph graph = generator.generate();

	std::cout << "Adjacency matrix:" << std::endl;
	graph.printAdjacencyMatrix();

	for (int i = 1; i <= Constants::nGraphs; i++) {
		std::stringstream dotFilename;
		dotFilename << Constants::graphNdot << i << ".dot";
		graph.generateDotFile(dotFilename.str());

		std::stringstream pngFilename;
		pngFilename << Constants::graphNpng << i << ".png";
		std::string command = "dot -Tpng " + dotFilename.str() + " -o " + pngFilename.str();
		system(command.c_str());

		std::cout << std::endl << "Test " << i << ":" << std::endl;
		graph.floydWarshall();
	}

	return 0;
}
