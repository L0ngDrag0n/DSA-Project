#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Order.h"
#include <iostream>
using namespace std;

// BinarySearchTree class declaration
class BinarySearchTree {
private:
    class TreeNode {
    public:
        Order data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const Order& order);
    };

    TreeNode* root;

    TreeNode* insert(TreeNode* node, const Order& order);
    TreeNode* search(TreeNode* node, const string& orderID) const;
    void destroyTree(TreeNode* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();
    void insertOrder(const Order& order);
    void searchOrder(const string& orderID) const;
};

#endif
