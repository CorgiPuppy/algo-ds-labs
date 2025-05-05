#ifndef RB_TREE_H
#define RB_TREE_H

#include <vector>
#include "TreeNode.h"

template <typename T>
class RBTree {
private:
    TreeNode<T>* root;
    int size;

    void clearHelper(TreeNode<T>* node) {
        if (node) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    void rotateLeft(TreeNode<T>* x) {
        TreeNode<T>* y = x->right;
        x->right = y->left;
        
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
    }

    void rotateRight(TreeNode<T>* x) {
        TreeNode<T>* y = x->left;
        x->left = y->right;
        
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        
        y->parent = x->parent;
        
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        
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
                    if (z->parent->parent != nullptr) {
                        z->parent->parent->color = RED;
                        rotateRight(z->parent->parent);
                    }
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
                    if (z->parent->parent != nullptr) {
                        z->parent->parent->color = RED;
                        rotateLeft(z->parent->parent);
                    }
                }
            }
        }
        root->color = BLACK;
    }

    TreeNode<T>* searchNode(const T& value) const {
        TreeNode<T>* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return current;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
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
    RBTree() : root(nullptr), size(0) {}
    ~RBTree() { clearHelper(root); }

    void insert(const T& value) {
        TreeNode<T>* z = new TreeNode<T>(value);
        z->color = RED;
        z->left = z->right = nullptr;
        
        TreeNode<T>* y = nullptr;
        TreeNode<T>* x = root;

        while (x != nullptr) {
            y = x;
            if (z->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->data < y->data) {
            y->left = z;
        } else {
            y->right = z;
        }

        fixInsert(z);
        size++;
    }

    bool search(const T& value) const {
        return searchNode(value) != nullptr;
    }

    int getSize() const { return size; }

    int getMaxDepth() const {
        return getMaxDepthHelper(root);
    }

    std::vector<int> getAllDepths() const {
        std::vector<int> depths;
        collectAllDepths(root, depths, 0);
        return depths;
    }

    std::vector<int> getLeafDepths() const {
        std::vector<int> leafDepths;
        collectLeafDepths(root, leafDepths, 0);
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
