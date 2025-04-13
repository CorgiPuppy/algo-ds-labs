#ifndef RB_TREE_H
#define RB_TREE_H

#include <vector>

#include "TreeNode.h"

template <typename T>
class RBTree {
	private:
		TreeNode<T>* root;
		int size;
		
		void rotateLeft(TreeNode<T>* x) {
			TreeNode<T>* y = x->right;
			x->right = y->left;
			if (y->left != nullptr)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void rotateRight(TreeNode<T>* x) {
			TreeNode<T>* y = x->left;
			x->left = y->right;
			if (y->right != nullptr)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void fixInsert(TreeNode<T>* z) {
			while (z->parent != nullptr && z->parent->color == RED) {
				if (z->parent == z->parent->parent->left) {
					TreeNode<T>* y = z->parent->parent->right;
					if (y != nullptr && y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					} else {
						if (z == z->parent->right) {
							z = z->parent;
							rotateLeft(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotateRight(z->parent->parent);
					}
				} else {
					TreeNode<T>* y = z->parent->parent->left;
					if (y != nullptr && y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					} else {
						if (z == z->parent->left) {
							z = z->parent;
							rotateRight(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotateRight(z->parent->parent);
					}
				}
			}
			root->color = BLACK;
		}

		TreeNode<T>* searchNode(const T& value) const {
			TreeNode<T>* current = root;
			while (current) {
				if (value == current->data)
					return current;
				else if (value < current->data)
					current = current->left;
				else
					current = current->right;
			}
			return nullptr;
		}

		int getMaxDepthHelper(TreeNode<T>* node) const {
			if (!node) return 0;
			return 1 + std::max(getMaxDepthHelper(node->left), getMaxDepthHelper(node->right));
		}

		void collectDepthsHelper(TreeNode<T>* node, std::vector<int>& depths, int currentDepth) const {
			if (!node) {
				depths.push_back(currentDepth);
				return;
			}
			collectDepthsHelper(node->left, depths, currentDepth + 1);
			collectDepthsHelper(node->right, depths, currentDepth + 1);
		}

		public:
			RBTree() : root(nullptr), size(0) {}

			void insert(const T& value) {
				TreeNode<T>* z = new TreeNode<T>(value);
				z->color = RED;
				TreeNode<T>* y = nullptr;
				TreeNode<T>* x = root;
				
				while (x) {
					y = x;
					if (z->data < x->data)
						x = x->left;
					else
						x = x->right;
				}
				
				z->parent = y;
				if (y == nullptr)
					root = z;
				else if (z->data < y->data)
					y->left = z;
				else
					y->right = z;

				fixInsert(z);
				size++;
			}

			bool search(const T& value) const {
				return searchNode(value) != nullptr;
			}

			int getSize() const { return size; }

			int getMaxDepth() const { return getMaxDepthHelper(root); }

			std::vector<int> getAllDepths() const {
				std::vector<int> depths;
				collectDepthsHelper(root, depths, 0);
				return depths;
			}
};

#endif
