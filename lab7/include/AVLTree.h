#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <vector>
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

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
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
        }

        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void collectLeafDepths(TreeNode<T>* node, std::vector<int>& depths, int currentDepth) const {
        if (!node) return;
        if (!node->left && !node->right) {
            depths.push_back(currentDepth);
            return;
        }
        collectLeafDepths(node->left, depths, currentDepth + 1);
        collectLeafDepths(node->right, depths, currentDepth + 1);
    }

    void collectAllDepths(TreeNode<T>* node, std::vector<int>& depths, int currentDepth) const {
        if (!node) {
            depths.push_back(currentDepth);
            return;
        }
        collectAllDepths(node->left, depths, currentDepth + 1);
        collectAllDepths(node->right, depths, currentDepth + 1);
    }

public:
    AVLTree() : BinarySearchTree<T>() {}

    void insert(const T &value) { this->root = insertNode(this->root, value); }

    int getMaxDepth() const {
        return getMaxDepthHelper(this->root);
    }

    std::vector<int> getAllDepths() const {
        std::vector<int> depths;
        collectAllDepths(this->root, depths, 0);
        return depths;
    }

    std::vector<int> getLeafDepths() const {
        std::vector<int> leafDepths;
        collectLeafDepths(this->root, leafDepths, 0);
        return leafDepths;
    }

private:
    int getMaxDepthHelper(TreeNode<T>* node) const {
        if (!node) return 0;
        return 1 + std::max(getMaxDepthHelper(node->left), 
                      getMaxDepthHelper(node->right));
    }
};

#endif
