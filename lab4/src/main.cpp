#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/Constants.h"
#include "../include/GraphGenerator.h"

int main() {
    GraphGenerator generator(Constants::minVertices, Constants::maxVertices, Constants::minEdges, Constants::maxEdges, Constants::maxDegree, Constants::directed);

	std::ofstream resultsFile(Constants::bfs_dfs);
	
    for (int i = 1; i <= Constants::Ngraphs; i++) {
        std::cout << "Генерация графа " << i << ":\n";

        Graph graph = generator.generate(i);

        int vertices = graph.getNvertices();
        int edges = graph.getNedges();

		std::stringstream dotFilename;
		dotFilename << Constants::graphNdot << i << ".dot";
		graph.generateDotFile(dotFilename.str());

		std::stringstream pngFilename;
		pngFilename << Constants::graphNpng << i << ".png";
		std::string command = "dot -Tpng " + dotFilename.str() + " -o " + pngFilename.str();
		system(command.c_str());

        graph.printGraph();

        std::cout << "Количество вершин: " << vertices << std::endl;
        std::cout << "Количество рёбер: " << graph.getNedges() << std::endl;

        std::cout << "Степени вершин (первые 5):\n";
        for (int j = 1; j <= 5 && j <= Constants::printNelements; j++) {
            std::cout << "  Вершина " << j << ": исходящая степень = " << graph.getOutDegree(j)
                      << ", входящая степень = " << graph.getInDegree(j) << std::endl;
        }

        int** adjacencyMatrix = graph.getAdjacencyMatrix();
        std::cout << "Матрица смежности (первые 5х5 элементов):" << std::endl;
        for (int row = 1; row <= Constants::printNelements; row++) {
            for (int col = 1; col <= Constants::printNelements; col++)
                std::cout << adjacencyMatrix[row][col] << " ";
            std::cout << std::endl;
        }
        graph.freeAdjacencyMatrix(adjacencyMatrix);

        int** incidenceMatrix = graph.getIncidenceMatrix();
        std::cout << "Матрица инцидентности (первые 5х5 элементов):" << std::endl;
        for (int row = 1; row <= Constants::printNelements; row++) {
            for (int col = 1; col <= Constants::printNelements; col++)
                std::cout << incidenceMatrix[row][col] << " ";
            std::cout << std::endl;
        }
        graph.freeIncidenceMatrix(incidenceMatrix);

		std::cout << "Список смежности:" << std::endl;
		graph.printGraph();

		Edge* edgeList = graph.getEdgeList();
		std::cout << "Список рёбер:" << std::endl;
		for (int i = 0; i < edges; i++)
			std::cout << "Ребро " << i + 1 << ": (" << edgeList[i].src << ", " << edgeList[i].dest << ")" << std::endl;
		graph.freeEdgeList(edgeList);
		
		int start = std::rand() % vertices + 1;
		int end = std::rand() % vertices + 1;
		std::cout << "Поиск кратчайшего пути из вершины " << start << " в вершину " << end << std::endl;

		int bfsPathLength = 0;
		int* bfsPath = nullptr;
		clock_t bfsBegin = clock();
		graph.bfs(start, end, bfsPathLength, bfsPath);
		clock_t bfsEnd = clock();
		double bfsElapsed = double(bfsEnd - bfsBegin) / CLOCKS_PER_SEC;
		if (bfsPathLength > 0) {
			std::cout << "BFS: Кратчайший путь: ";
			for (int i = 0; i < bfsPathLength; i++) {
				std::cout << bfsPath[i];
				if (i < bfsPathLength - 1) std::cout << " -> ";
			}
			std::cout << std::endl;
		} else
			std::cout << "BFS: Путь не найден." << std::endl;
		std::cout << "Время выполнения: " << bfsElapsed << " секунд" << std::endl;
		
		delete [] bfsPath;
		
		int dfsPathLength = 0;
		int* dfsPath = nullptr;
		clock_t dfsBegin = clock();
		graph.dfs(start, end, dfsPathLength, dfsPath);
		clock_t dfsEnd = clock();
		double dfsElapsed = double(dfsEnd - dfsBegin) / CLOCKS_PER_SEC;
		if (dfsPathLength > 0) {
			std::cout << "DFS: Кратчайший путь: ";
			for (int i = 0; i < dfsPathLength; i++) {
				std::cout << dfsPath[i];
				if (i < dfsPathLength - 1) std::cout << " -> ";
			}
			std::cout << std::endl;
		} else
			std::cout << "DFS: Путь не найден." << std::endl;	
		std::cout << "Время выполнения: " << dfsElapsed << " секунд" << std::endl;

		delete [] dfsPath;

		resultsFile << vertices << " " << bfsElapsed << " " << dfsElapsed << std::endl;

		std::cout << std::endl;
    }

    return 0;
}
