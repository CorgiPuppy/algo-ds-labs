#ifndef TREE_NODE_H
#define TREE_NODE_H

enum Color { RED, BLACK };

template <typename T>
class TreeNode {
	public:
		T data;
		TreeNode<T>* left;
		TreeNode<T>* right;
		TreeNode<T>* parent;

		Color color;

		int height;
		
		TreeNode(const T &value) : data(value), left(nullptr), right(nullptr), parent(nullptr), color(RED), height(1) {}
};

#endif
