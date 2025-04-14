#ifndef CARTESIAN_TREE_H
#define CARTESIAN_TREE_H

#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "Constants.h"
#include "TreeNode.h"
#include "SearchResult.h"

template <typename T>
class CartesianTree {
private:
    TreeNode<T>* root;
    int size;

    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

    TreeNode<T>* merge(TreeNode<T>* left, TreeNode<T>* right) {
        if (!left || !right) 
            return left ? left : right;

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        } else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    void split(TreeNode<T>* current, T key, TreeNode<T>*& left, TreeNode<T>*& right) {
        if (!current) {
            left = nullptr;
            right = nullptr;
        } else if (current->data <= key) {
            split(current->right, key, current->right, right);
            left = current;
        } else {
            split(current->left, key, left, current->left);
            right = current;
        }
    }

    TreeNode<T>* insertNode(TreeNode<T>* node, const T& value, int priority) {
        if (!node) {
            size++;
            return new TreeNode<T>(value, priority);
        }

        if (priority > node->priority) {
            TreeNode<T>* left = nullptr;
            TreeNode<T>* right = nullptr;
            split(node, value, left, right);

            TreeNode<T>* newNode = new TreeNode<T>(value, priority);
            newNode->left = left;
            newNode->right = right;
            return newNode;
        }

        if (value < node->data)
            node->left = insertNode(node->left, value, priority);
        else
            node->right = insertNode(node->right, value, priority);
        
        return node;
    }

    int getMaxDepthHelper(TreeNode<T>* node) const {
        if (!node) return 0;
        return 1 + std::max(getMaxDepthHelper(node->left), 
                          getMaxDepthHelper(node->right));
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
    CartesianTree() : root(nullptr), size(0), gen(std::random_device{}()), dist(Constants::minValue, Constants::maxValue) {}

    void insert(const T& value) {
        int priority = dist(gen);
        root = insertNode(root, value, priority);
        size++;
    }

    bool search(const T& value) const {
        TreeNode<T>* current = root;
        while (current) {
            if (value == current->data) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }

    void remove(const T& value) {
        root = deleteNode(root, value);
    }

    int getSize() const { return size; }
    
    int getMaxDepth() const { return getMaxDepthHelper(root); }

    std::vector<int> getAllDepths() const {
        std::vector<int> depths;
        collectDepthsHelper(root, depths, 0);
        return depths;
    }

private:
    TreeNode<T>* deleteNode(TreeNode<T>* node, const T& value) {
        if (!node) return nullptr;

        if (value == node->data) {
            TreeNode<T>* merged = merge(node->left, node->right);
            delete node;
            size--;
            return merged;
        }

        if (value < node->data)
            node->left = deleteNode(node->left, value);
        else
            node->right = deleteNode(node->right, value);

        return node;
    }
};

#endif
