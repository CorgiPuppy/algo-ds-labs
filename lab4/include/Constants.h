#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
	int minVertices = 10;
    int maxVertices = 100;
    int minEdges = 10;
    int maxEdges = 100;
    int maxDegree = 1000;
    bool directed = false;
	
	int Ngraphs = 10;
	int printNelements = 5;

	std::string bfs_dfs = "plots/dat-files/bfs_dfs.dat";
	std::string graphNdot = "assets/files/graph_";
	std::string graphNpng = "assets/pictures/graph_";
}

#endif
