#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

#include "EdgeNode.h"

class Graph {
	private:
		std::vector<EdgeNode*> edges;
		std::vector<int> degree;
		int nvertices;
		int nedges;
		bool directed;

	public:
		Graph(int vertices, bool isDirected) : nvertices(vertices),  nedges(0), directed(isDirected) {
			edges.resize(vertices + 1, nullptr);
			degree.resize(vertices + 1, 0);
		}

		~Graph() {
			for (int i = 1; i <= nvertices; i++) {
				EdgeNode* current = edges[i];
				while (current != nullptr) {
					EdgeNode* temp = current;
					current = current->next;
					delete temp;
				}
			}
		}

		void addEdge(int src, int dest) {
			EdgeNode* newEdge = new EdgeNode(dest);
			newEdge->next = edges[src];
			edges[src] = newEdge;
			degree[src]++;
			nedges++;

			if (!directed) {
				newEdge = new EdgeNode(src);
				newEdge->next = edges[dest];
				edges[dest] = newEdge;
				degree[dest]++;
			}
		}

		void printGraph() const {
			for (int i = 1; i <= nvertices; i++) {
				std::cout << "Вершина " << i << ": ";
				EdgeNode* current = edges[i];
				while (current != nullptr) {
					std::cout << current->vertex << " ";
					current = current->next;
				}
				std::cout << std::endl;
			}
		}

		int getNedges() const { return nedges; }

		int getDegree(int vertex) const { return degree[vertex]; }
};

#endif
