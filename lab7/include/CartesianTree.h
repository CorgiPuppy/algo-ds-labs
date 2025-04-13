#ifndef CARTESIAN_TREE_H
#define CARTESIAN_TREE_H

#include <random>
#include <chrono>
#include <vector>

#include "Constants.h"
#include "TreeNode.h"
#include "SearchResult.h"

template <typename T>
class Treap {
	private:
		TreeNode<T>* root;
		int size;

		std::mt19937 gen;
		std::uniform_int_discribution<int>dist;

		TreeNode<T>* merge(TreeNode<T>* left, TreeNode<T>* right) {
			if (!left) return right;
			if (!right) return left;

			if (left->height > right->height) {
				left->right = merge(left->right, right);
				return left;
			} else {
				right->left = merge(left, right->left);
				return right;
			}
		}

		void split(TreeNode<T>* node, T key, TreeNode<T>*& left, TreeNode<T>*& right) {
			if (!node) {
				left = nullptr;
				right = nullptr;
				return;
			}

			if (node->data <= key) {
				split(node->right, key, node->right, right);
				left = node;
			} else {
				split(node->left, key, left, node->left);
				right = node;
			}
		}

		int getHeight(TreeNode<T>* node) const {
			return node ? node->height : 0;
		}

		int getMaxDepth(TreeNode<T>* node) const {
			if (!node) return 0;
			return 1 + std::max(getMaxDepth(node->left), getMaxDepth(node->right));
		}

	public:
		CartesianTree() : root(nullptr), size(0), gen(std::random_device{}()), dist(Constants::minValue, Constants::maxValue) {}

		void insert(const T& value) {
			TreeNode<T>* left;
			TreeNode<T>* right;

			split(root, value, left, right);

			TreeNode<T>* newNode = new TreeNode<T>(value);
			newNode->height = dist(gen);

			root = merge(merge(left, newNode), right);
			size++;
		}

		bool search(const T& value) const {
			TreeNode<T>* current = root;
			while (current) {
				if (current->data == value)
					return true;
				else if (value < current->data)
					current = current->left;
				else
					current = current->right;
			}
			return false;
		}

		void remove(const T& value) {
			TreeNode<T>* left;
			TreeNode<T>* mid;
			TreeNode<T>* right;

			split(root, value - 1, left, right);
			split(right, value, mid, right);

			if (mid && mid->data == value) {
				delete mid;
				size--;
			}

			root = merge(left, right);
		}

		int getSize() const { return size; }
		
		int getMaxDepth() const { return getMaxDepth(root); }

		void collectDepths(TreeNode<T>* node, std::vector<int>&depth, int currentDepth) const {
			if (!node) {
				depths.push_back(currentDepth);
				return;
			}
			collectDepths(node->left, depths, currentDepth + 1);
			collectDepths(node->right, depths, currentDepth + 1);
		}

		std::vector<int> getAllDepths() const {
			std::vector<int> depths;
			collectDepths(root, depths, 0);
			return depths;
		}
};

#endif
