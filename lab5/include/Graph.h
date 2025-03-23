#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

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

			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					matrix[i][current->vertex] = current->weight;
					current = current->next;
				}
			}

			for (int i = 1; i <= nVertices; i++) {
				for (int j = 1; j <= nVertices; j++)
					std::cout << matrix[i][j] << " ";
				std::cout << std::endl;
			}

			for (int i = 0; i <= nVertices; i++)
				delete [] matrix[i];
			delete [] matrix;
		}
};

#endif
