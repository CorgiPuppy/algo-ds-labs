#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
	int maxWeight = 20;

	int minVertices[4] = { 10, 20, 27, 35 };
	int maxVertices[4] = { 10, 20, 27, 35 };

	int minEdges[4] = { 3, 4, 10, 20 } ;

	int nTests = 4;
    int nGraphs = 5;

    std::string graphNdot = "assets/files/graph_";
	std::string graphNpng = "assets/pictures/graph_";
	
	std::string floyd_warshall = "plots/dat-files/floyd_warshall.dat";
}

#endif
