#ifndef EDGE_H
#define EDGE_H

class Edge {
	public:
		int src;
		int dest;
		Edge(int s, int d) : src(s), dest(d) {}
		Edge() : src(0), dest(0) {}
};

#endif
