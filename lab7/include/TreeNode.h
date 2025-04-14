#ifndef TREE_NODE_H
#define TREE_NODE_H

enum Color { RED, BLACK };

template <typename T>
class TreeNode {
	public:
		T data;
		TreeNode<T>* left;
		TreeNode<T>* right;

		int height;

		int priority;

		TreeNode<T>* parent;
		Color color;
	
		TreeNode(const T &value, int prio = 0) : data(value), left(nullptr), right(nullptr), height(1), priority(prio), parent(nullptr), color(RED) {}
};

#endif
