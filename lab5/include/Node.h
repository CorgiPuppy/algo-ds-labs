#ifndef NODE_H
#define NODE_H

class Node {
	public:
		int vertex;
		int weight;
		Node* next;
		Node(int v, int w) : vertex(v), weight(w), next(nullptr) {}
};

#endif
