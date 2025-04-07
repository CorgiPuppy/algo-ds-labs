#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>

#include "BinarySearchTree.h"

template <typename T>
class AVLTree : public BinarySearchTree<T> {
	private:
		int height(TreeNode<T>* node) const {
			return node ? node->height : 0;
		}

		int balanceFactor(TreeNode<T>* node) const {
			return node ? height(node->left) - height(node->right) : 0;
		}

		TreeNode<T>* rotateRight(TreeNode<T>* y) {
			TreeNode<T>* x = y->left;
			TreeNode<T>* T2 = x->right;

			x->right = y;
			y->left = T2;

			x->height = std::max(height(x->left), height(x->right)) + 1;
			y->height = std::max(height(y->left), height(y->right)) + 1;

			return y;
		}

		TreeNode<T>* rotateLeft(TreeNode<T>* x) {
			TreeNode<T>* y = x->right;
			TreeNode<T>* T2 = y->left;

			y->left = x;
			x->right = T2;

			x->height = std::max(height(x->left), height(x->right)) + 1;
			y->height = std::max(height(y->left), height(y->right)) + 1;

			return y;
		}

		TreeNode<T>* insertNode(TreeNode<T>* node, const T &value) {
			if (!node) {
				this->size++;
				return new TreeNode<T>(value);
			}
			
			if (value < node->data)
				node->left = insertNode(node->left, value);
			else if (value > node->data)
				node->right = insertNode(node->right, value);
			else
				return node;

			node->height = 1 + std::max(height(node->left), height(node->right));

			int balance = balanceFactor(node);

			if (balance > 1 && value < node->left->data)
				return rotateRight(node);

			if (balance < -1 && value > node->right->data)
				return rotateLeft(node);

			if (balance > 1 && value > node->left->data) {
				node->left = rotateLeft(node->left);
				return rotateRight(node);
			
			if (balance < -1 && value < node->right->data) {
				node->right = rotateRight(node->right);
				return rotateLeft(node);
			}

			return node;
		}
	
	public:
		AVLTree() : BinarySearchTree<T>() {}

		void insert(const T &value) { this->root = insertNode(this->root, value); }
};

#endif
