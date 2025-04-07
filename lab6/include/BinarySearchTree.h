#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

#include "TreeNode.h"

template <typename T>
class BinarySearchTree {
	protected:
		TreeNode<T>* root;
		int size;

		TreeNode<T>* insertNode(TreeNode<T>* node, const T &value) {
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

		void inOrderTraversal(TreeNode<T>* node) const {
			if (!node) return;
			inOrderTraversal(node->left);
			std::cout << node->data << " ";
			inOrderTraversal(node->right);
		}

		TreeNode<T>* deleteNode(TreeNode<T>* node, const T &value) {
			if (!node) return node;

			if (value < node->data)
				node->left = deleteNode(node->left, value);
			else if (value > node->data)
				node->right = deleteNode(node->right, value);
			else {
				if (!node->left) {
					TreeNode<T>* temp = node->right;
					delete node;
					size--;
					return temp;
				} else if (!node->right) {
					TreeNode<T>* temp = node->left;
					delete node;
					size--;
					return temp;
				}

				TreeNode<T>* temp = minValueNode(node->right);
				node->data = temp->data;
				node->right = deleteNode(node->right, temp->data);
			}

			return node;
	}

	TreeNode<T>* minValueNode(TreeNode<T>* node) {
		TreeNode<T>* current = node;
		while (current && current->left)
			current = current->left;
		return current;
	}

	void deleteNode(const T &value) { root = deleteNode(root, value); }
	public:
		BinarySearchTree() : root(nullptr), size(0) {}

		void insert(const T &value) { root = insertNode(root, value); }
		bool search(const T &value) const { return searchNode(root, value); }
		void inOrder() const { inOrderTraversal(root); std::cout << "\n"; }
		int getSize() const { return size; }
};

#endif
