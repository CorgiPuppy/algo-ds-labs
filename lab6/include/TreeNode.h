#ifndef TREE_NODE_H
#define TREE_NODE_H

template <typename T>
class TreeNode {
	public:
		T data;
		TreeNode<T>* left;
		TreeNode<T>* right;

		int height;
		
		TreeNode(const T &value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

#endif
