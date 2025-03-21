#ifndef NODE_H
#define NODE_H

class Node {
	public:
		int data;
		EdgeNode* next;
		EdgeNode(int d) : data(d), next(nullptr) {}
};

#endif
