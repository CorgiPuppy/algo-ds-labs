#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <string>
#include <fstream>

#include "Node.h"

class Graph {
	private:
		Node** edges;
		int nVertices;
		int nEdges;

	public:
		Graph(int vertices) : nVertices(vertices), nEdges(0) {
			edges = new Node*[vertices + 1];
			for (int i = 0; i <= vertices; i++)
				edges[i] = nullptr;
		}

		~Graph() {
			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					Node* temp = current;
					current = current->next;
					delete temp;;
				}
			}
			delete [] edges;
		}

		void addEdge(int src, int dest, int weight) {
			if (src == dest) return;

			Node* current = edges[src];
			while (current) {
				if (current->vertex == dest) return;
				current = current->next;
			}

			Node* newNode = new Node(dest, weight);
			newNode->next = edges[src];
			edges[src] = newNode;
			nEdges++;

			newNode = new Node(src, weight);
			newNode->next = edges[dest];
			edges[dest] = newNode;
			nEdges++;
		}

		void printAdjacencyMatrix() {
			int** matrix = new int*[nVertices + 1];
			for (int i = 0; i <= nVertices; i++)
				matrix[i] = new int[nVertices + 1];

			std::cout << "   ";
			for (int i = 1; i <= nVertices; i++)
				printf("%3d", i);
			std::cout << std::endl;

			for (int i = 1; i <= nVertices; i++) {
				printf("%3d", i);
				for (int j = 1; j <= nVertices; j++) {
					Node* current = edges[i];
					bool found = false;
					while (current) {
						if (current->vertex == j) {
							printf("%3d", current->weight);
							found = true;
							break;
						}
						current = current->next;
					}
					if (!found)
						printf("%3s", " ");
				}
				std::cout << std::endl;
			}

			for (int i = 0; i <= nVertices; i++)
				delete [] matrix[i];
			delete [] matrix;
		}

		void floydWarshall() {
			int** dist = new int*[nVertices + 1];
			for (int i = 0; i <= nVertices; i++) {
				dist[i] = new int[nVertices +1];
				for (int j = 0; j <= nVertices; j++) {
					if (i == j)
						dist[i][j] = 0;
					else
						dist[i][j] = INT_MAX;
				}
			}

			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					dist[i][current->vertex] = current->weight;
					current = current->next;
				}
			}

			for (int k = 1; k <= nVertices; k++)
				for (int i = 1; i <= nVertices; i++)
					for (int j = 1; j <= nVertices; j++)
						if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] > dist[i][j] + dist[k][j])
							dist[i][j] = dist[i][k] + dist[k][j];

			std::cout << "Матрица кратчайших расстояний:" << std::endl;
			std::cout << "   ";
			for (int i = 1; i <= nVertices; i++)
				printf("%3d", i);
			std::cout << std::endl;

			for (int i = 1; i <= nVertices; i++) {
				printf("%3d", i);
				for (int j = 1; j <= nVertices; j++) {
					if (dist[i][j] == INT_MAX) {
						printf("%5s", "INF ");
					} else {
						printf("%3d", dist[i][j]);
					}
				}
				std::cout << std::endl;
			}

			for (int i = 0; i <= nVertices; i++) {
				delete[] dist[i];
			}
			delete[] dist;
		}

		void generateDotFile(const std::string& filename) const {
			std::ofstream dotFile(filename);
			if (!dotFile.is_open()) {
				std::cerr << "Error of opening file " << filename << " for writing." << std::endl;
				return;
			}

			dotFile << "graph G {\n";
			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					if (i <= current->vertex)
						dotFile << " " << i << " -- " << current->vertex << ";\n";
					current = current->next;
				}
			}
			dotFile << "}\n";
			dotFile.close();
		}
};

#endif
