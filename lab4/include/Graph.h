#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <fstream>

#include "Node.h"
#include "Edge.h"
#include "Queue.h"
#include "Stack.h"

class Graph {
	private:
		Node** edges;
		int* outDegree;
		int* inDegree;
		int nVertices;
		int nEdges;
		bool directed;

	public:
		Graph(int vertices, bool isDirected) : nVertices(vertices),  nEdges(0), directed(isDirected) {
			edges = new Node*[vertices + 1];
			outDegree = new int[vertices + 1];
			inDegree = new int[vertices + 1];

			for (int i = 0; i <= vertices; i++) {
				edges[i] = nullptr;
				outDegree[i] = 0;
				inDegree[i] = 0;
			}
		}

		~Graph() {
			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					Node* temp = current;
					current = current->next;
					delete temp;
				}
			}

			delete [] edges;
			delete [] outDegree;
			delete [] inDegree;
		}

		void addEdge(int src, int dest) {
			if (src == dest)
				return;

			Node* current = edges[src];
			while (current) {
				if (current->vertex == dest)
					return;
				current = current->next;
			}

			Node* newEdge = new Node(dest);
			newEdge->next = edges[src];
			edges[src] = newEdge;
			outDegree[src]++;
			inDegree[dest]++;
			nEdges++;

			if (!directed) {
				Node* reverseEdge = new Node(src);
				reverseEdge->next = edges[dest];
				edges[dest] = reverseEdge;
				outDegree[dest]++;
				inDegree[src]++;
			}
		}

		void printGraph() const {
			for (int i = 1; i <= nVertices; i++) {
				std::cout << "Вершина " << i << ": ";
				Node* current = edges[i];
				while (current != nullptr) {
					std::cout << current->vertex << " ";
					current = current->next;
				}
				std::cout << std::endl;
			}
		}

		int** getAdjacencyMatrix() const {
			int** matrix = new int*[nVertices + 1];
			for (int i = 0; i <= nVertices; i++)
				matrix[i] = new int[nVertices + 1]();

			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					matrix[i][current->vertex] = 1;
					current = current->next;
				}
			}

			return matrix;
		}

		void freeAdjacencyMatrix(int** matrix) const {
			for (int i = 0; i <= nVertices; i++)
				delete [] matrix[i];

			delete [] matrix;
		}

		int** getIncidenceMatrix() const {
			int** matrix = new int*[nVertices + 1];
			for (int i = 0; i <= nVertices; i++)
				matrix[i] = new int[nEdges + 1]();

			int edgeIndex = 1;
			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					if (directed || i < current->vertex) {
						if (directed) {
							matrix[i][edgeIndex] = -1;
							matrix[current->vertex][edgeIndex] = 1;
						} else {
							matrix[i][edgeIndex] = 1;
							matrix[current->vertex][edgeIndex] = 1;
						}
						edgeIndex++;
					}
					current = current->next;
				}
			}

			return matrix;
		}

		void freeIncidenceMatrix(int** matrix) const {
			for (int i = 0; i <= nVertices; i++)
				delete [] matrix[i];

			delete [] matrix;
		}
		
		Edge* getEdgeList() const {
			Edge* edgeList = new Edge[nEdges];
			int edgeIndex = 0;

			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					if (directed || i < current->vertex) {
						edgeList[edgeIndex++] = Edge(i, current->vertex);
					}
					current = current->next;
				}
			}

			return edgeList;
		}	

		void freeEdgeList(Edge* edgeList) const {
			delete [] edgeList;
		}

		void bfs(int start, int end, int& pathLength, int*& path) const {
			bool* discovered = new bool[nVertices + 1];
			bool* processed = new bool[nVertices + 1];
			int* parent = new int[nVertices + 1];

			for (int i = 1; i <= nVertices; i++) {
				discovered[i] = processed[i] = false;
				parent[i] = -1;
			}

			Queue q(nVertices);
			q.enqueue(start);
			discovered[start] = true;

			while (!q.isEmpty()) {
				int v = q.dequeue();
				processed[v] = true;

				Node* current = edges[v];
				while (current) {
					int y = current->vertex;
					if (!processed[y] || directed) {
						if (!discovered[y]) {
							q.enqueue(y);
							discovered[y] = true;
							parent[y] = v;
						}
					}
						
					current = current->next;
				}
			}

			if (!processed[end]) {
				pathLength = 0;
				path = nullptr;
			} else {
				pathLength = 0;
				int current = end;
				while (current != -1) {
					pathLength++;
					current = parent[current];
				}

				path = new int[pathLength];
				current = end;
				for (int i = pathLength - 1; i >= 0; i--) {
					path[i] = current;
					current = parent[current];
				}
			}

			delete [] discovered;
			delete [] processed;
			delete [] parent;
		}

		void dfs(int start, int end, int& pathLength, int*& path) const {
			bool* discovered = new bool[nVertices + 1];
			bool* processed = new bool[nVertices + 1];
			int* parent = new int[nVertices + 1];

			for (int i = 1; i <= nVertices; i++) {
				discovered[i] = processed[i] = false;
				parent[i] = -1;
			}

			Stack stack(nVertices);
			stack.push(start);
			discovered[start] = true;

			while (!stack.isEmpty()) {
				int v = stack.pop();
				if (!processed[v]) {
					processed[v] = true;

					Node* current = edges[v];
					while (current) {
						int y = current->vertex;
						if (!discovered[y]) {
							stack.push(y);
							discovered[y] = true;
							parent[y] = v;
						}
						
						current = current->next;
					}
				}
			}

			if (!processed[end]) {
				pathLength = 0;
				path = nullptr;
			} else {
				pathLength = 0;
				int current = end;
				while (current != -1) {
					pathLength++;
					current = parent[current];
				}
				
				path = new int[pathLength];
				current = end;
				for (int i = pathLength - 1; i >= 0; i--) {
					path[i] = current;
					current = parent[current];
				}
			}

			delete [] discovered;
			delete [] processed;
			delete [] parent;
		}

		void generateDotFile(const std::string& filename) const {
			std::ofstream dotFile(filename);
			if (!dotFile.is_open()) {
				std::cerr << "Error of opening file " << filename << " for writing." << std::endl;
				return;
			}

			dotFile << (directed ? "digraph G {\n" : "graph G {\n");
			for (int i = 1; i <= nVertices; i++) {
				Node* current = edges[i];
				while (current) {
					if (directed || i <= current->vertex)
						dotFile << " " << i << (directed ? " -> " : " -- ") << current->vertex << ";\n";
					current = current->next;
				}
			}
			dotFile << "}\n";
			dotFile.close();
		}

		int getNvertices() const { return nVertices; }

		int getNedges() const { return nEdges; }

		int getOutDegree(int vertex) const { return outDegree[vertex]; }

		int getInDegree(int vertex) const { return inDegree[vertex]; }
};

#endif
