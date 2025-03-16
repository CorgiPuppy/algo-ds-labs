#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <ctime>

#include "Graph.h"

class GraphGenerator {
	private:
		int minVertices;
		int maxVertices;
		int minEdges;
		int maxEdges;
		int maxDegree;
		bool directed;

	public:
		GraphGenerator(int minV, int maxV, int minE, int maxE, int maxD, bool isDirected) :
		minVertices(minV),
		maxVertices(maxV),
		minEdges(minE),
		maxEdges(maxE),
		maxDegree(maxD),
		directed(isDirected) {
			std::srand(std::time(0));
		}

		Graph generate() {
			int vertices = minVertices + std::rand() % (maxVertices + 1 - minVertices);
			int edges = minEdges + std::rand() % (maxEdges + 1 - minEdges);

			Graph graph(vertices, directed);

			for (int i = 0; i < edges; i++) {
				int src = std::rand() % vertices + 1;
				int dest = std::rand() % vertices + 1;

				if (graph.getDegree(src) < maxDegree && graph.getDegree(dest) < maxDegree)
					graph.addEdge(src, dest);	
			}

			return graph;
		}
};

#endif
