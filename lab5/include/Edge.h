#ifndef EDGE_H
#define EDGE_H

class Edge {
	public:
		int src;
		int dest;
		int weight;
		Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
		Edge() : src(0), dest(0), weight(0) {}
};

#endif
