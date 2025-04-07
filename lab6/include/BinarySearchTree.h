#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

#include "TreeNode.h"

template <typename T>
class BinarySearchTree {
	protected:
		TreeNode<T>* root;
		int size;

		TreeNode<T> insertNode(TreeNode<T>* node, const T &value) {
			if (!node) {
				size++;
				return new TreeNode<T>(value);
			}
			
			if (value < node->data)
				node->left = insertNode(node->left, value);
			else if (value > node->data)
				node->right = insertNode(node->right, value);
			return node;
		}
		
		bool searchNode(TreeNode<T>* node, const T &value) const {
			if (!node) return false;
			if (value == node->data) return true;
			return (value < node->data) ? searchNode(node->left, value) : searchNode(node->right, value);
		}

		void printTree(TreeNode<T>* node) const {
			if (!node) return;
			printTree(node->left);
			std::cout << node->data << " ";
			printTree(node->right);
		}

	public:
		BinarySearchTree() : root(nullptr), size(0) {}

		void insert(const T &value) { root = insertNode(root, value); }
		bool search(const T &value) const { return searchNode(root, value); }
		void print() const { printTree(root); std::cout << "\n"; }
		int getSize() const { return size; }
};

#endif
