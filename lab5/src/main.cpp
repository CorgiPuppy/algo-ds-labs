#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/GraphGenerator.h"
#include "../include/Constants.h"

int main() {
	double executionTimes[Constants::nTests] = {0};

	for (int sizeIndex = 0; sizeIndex < 3; sizeIndex++) {

		GraphGenerator generator(Constants::minVertices[sizeIndex], Constants::maxVertices[sizeIndex], Constants::minEdges[sizeIndex], Constants::minEdges[sizeIndex]);
		for (int graphIndex = 0; graphIndex < Constants::nGraphs; graphIndex++) {

			Graph graph = generator.generate(sizeIndex);

			std::cout << "Graph " << graphIndex << " with " << Constants::minVertices[sizeIndex] << " vertices:" << std::endl;
			std::cout << "Adjacency matrix:" << std::endl;
			graph.printAdjacencyMatrix();

            std::stringstream dotFilename;
            dotFilename << Constants::graphNdot << "size_" << Constants::minVertices[sizeIndex] << "_graph_" << graphIndex + 1 << ".dot";
            graph.generateDotFile(dotFilename.str());

            std::stringstream pngFilename;
            pngFilename << Constants::graphNpng << "size_" << Constants::minVertices[sizeIndex] << "_graph_" << graphIndex + 1 << ".png";
            std::string command = "dot -Tpng " + dotFilename.str() + " -o " + pngFilename.str();
			system(command.c_str());

			std::cout << std::endl << "Test " << graphIndex << ":" << std::endl;
			graph.floydWarshall();
		}
	}

	return 0;
}
