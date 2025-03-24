#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "../include/GraphGenerator.h"
#include "../include/Constants.h"

int main() {
	double executionTimes[Constants::nTests] = {0.0};

	for (int sizeIndex = 0; sizeIndex < Constants::nTests; sizeIndex++) {
		GraphGenerator generator(Constants::minVertices[sizeIndex], Constants::maxVertices[sizeIndex], Constants::minEdges[sizeIndex], Constants::minEdges[sizeIndex]);

		double totalTime = 0.0;

		for (int graphIndex = 0; graphIndex < Constants::nGraphs; graphIndex++) {
			Graph graph = generator.generate(sizeIndex);

			std::cout << "Graph " << graphIndex + 1 << " with " << Constants::minVertices[sizeIndex] << " vertices:" << std::endl;
			std::cout << "Adjacency matrix:" << std::endl;
			graph.printAdjacencyMatrix();

            auto start = std::chrono::high_resolution_clock::now();
            graph.floydWarshall();
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> elapsed = end - start;
            totalTime += elapsed.count();
            std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

			std::stringstream dotFilename;
            dotFilename << Constants::graphNdot << "size_" << Constants::minVertices[sizeIndex] << "_" << graphIndex + 1 << ".dot";
            graph.generateDotFile(dotFilename.str());

            std::stringstream pngFilename;
            pngFilename << Constants::graphNpng << "size_" << Constants::minVertices[sizeIndex] << "_" << graphIndex + 1 << ".png";
            std::string command = "dot -Tpng " + dotFilename.str() + " -o " + pngFilename.str();
			system(command.c_str());
		}
		executionTimes[sizeIndex] = totalTime / Constants::nGraphs;
	}

	std::ofstream resultsFile(Constants::floyd_warshall);
    if (resultsFile.is_open()) {
        for (int i = 0; i < Constants::nTests; i++)
            resultsFile << Constants::minVertices[i] << " " << executionTimes[i] << std::endl;
        resultsFile.close();
    } else std::cerr << "Error: Unable to open results file." << std::endl;

	return 0;
}
