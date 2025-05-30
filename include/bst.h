// Copyright 2021 NNTU-CS
#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        } else if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        } else {
            node->count++;
        }
    }

    int search(Node* node, const T& key) const {
        if (!node) return 0;
        if (key == node->key) return node->count;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        inorder(node->left, out);
        out.push_back({node->key, node->count});
        inorder(node->right, out);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& key) { insert(root, key); }
    int search(const T& key) const { return search(root, key); }
    int depth() const { return depth(root); }
    void getAllWords(std::vector<std::pair<T, int>>& out) const { inorder(root, out); }
};

#endif // INCLUDE_BST_H_
