#include <iostream>
#include "../include/GraphGenerator.h"

int main() {
    int minVertices = 2;
    int maxVertices = 10;
    int minEdges = 2;
    int maxEdges = 10;
    int maxDegree = 10;
    bool directed = false;

    GraphGenerator generator(minVertices, maxVertices, minEdges, maxEdges, maxDegree, directed);

    for (int i = 1; i <= 10; i++) {
        std::cout << "Генерация графа " << i << ":\n";

        Graph graph = generator.generate();

        int vertices = graph.getNvertices();
        int edges = graph.getNedges();

        graph.printGraph();

        std::cout << "Количество вершин: " << vertices << std::endl;
        std::cout << "Количество рёбер: " << graph.getNedges() << std::endl;

        std::cout << "Степени вершин (первые 5):\n";
        for (int j = 1; j <= 5 && j <= vertices; j++) {
            std::cout << "  Вершина " << j << ": исходящая степень = " << graph.getOutDegree(j)
                      << ", входящая степень = " << graph.getInDegree(j) << std::endl;
        }

        int** matrix = graph.getAdjacencyMatrix();
        std::cout << "Матрица смежности (первые 5х5 элементов):" << std::endl;
        for (int row = 1; row <= vertices; row++) {
            for (int col = 1; col <= vertices; col++)
                std::cout << matrix[row][col] << " ";
            std::cout << std::endl;
        }
        graph.freeAdjacencyMatrix(matrix);

        std::cout << std::endl;
    }

    return 0;
}
