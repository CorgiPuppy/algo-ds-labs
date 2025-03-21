#ifndef NODE_H
#define NODE_H

class Node {
	public:
		int vertex;
		Node* next;
		Node(int v) : vertex(v), next(nullptr) {}
};

#endif
