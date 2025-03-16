#ifndef EDGE_NODE_H
#define EDGE_NODE_H

class EdgeNode {
	public:
		int vertex;
		EdgeNode* next;
		EdgeNode(int v) : vertex(v), next(nullptr) {}
};

#endif
