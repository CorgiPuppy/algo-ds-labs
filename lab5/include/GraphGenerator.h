#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <ctime>
#include <cstdlib>

#include "Graph.h"
#include "Constants.h"

class GraphGenerator {
	private:
		int minVertices;
		int maxVertices;
		int minEdges;
		int maxEdges;
	
	public:
		GraphGenerator(int minV, int maxV, int minE, int maxE) :
		minVertices(minV),
		maxVertices(maxV),
		minEdges(minE),
		maxEdges(maxE) {
			std::srand(std::time(0));
		}

		Graph generate() {
			int vertices = minVertices + std::rand() % (maxVertices + 1 - minVertices);

			Graph graph(vertices);

			for (int i = 1; i < vertices; i++) {
				int weight = std::rand() % Constants::maxWeight + 1;
				graph.addEdge(i, i + 1, weight);
			}

			for (int i = 1; i <= vertices; i++) {
				int edges = minEdges + std::rand() % (maxEdges - minEdges + 1);
				for (int j = 0; j < edges; j++) {
					int dest = std::rand() % vertices + 1;
					int weight = std::rand() % Constants::maxWeight + 1;
					if (i != dest) {
						graph.addEdge(i, dest, weight);
					}
				}
			}

			return graph;
		}
};

#endif
