//
// Created by Yotam Konopnicki on 14/05/2025.
//
#pragma once
#include <iostream>
template <typename T>
class Node {

public:
    T val;
    Node* right;
    Node* left;
    int height;

    Node(): right(nullptr), left(nullptr), height(0){};

    Node(T val): val(val), right(nullptr), left(nullptr), height(0){};

    Node(const Node& node) = default;

    Node& operator=(const Node& node) = default;

    ~Node() {
        delete left;
        delete right;
    }

    int getBalanceFactor() {
        if (right == nullptr && left == nullptr) {
            return 0;
        }
        if (right == nullptr) {
            return (left->height) + 1;
        }
        if (left == nullptr) {
            return (-(right->height)) - 1;
        }
        return (left->height)-(right->height);
    }
    void updateHeight() {
        if (left == nullptr && right == nullptr) {
            height = 0;
        }
        if (left == nullptr && right != nullptr) {
            height = 1 + right->height;
        }
        if (right == nullptr && left != nullptr) {
            height = 1 + left->height;
        }
        if (left != nullptr && right != nullptr) {
            if (left->height > right->height) {
                height = 1+ left->height;
            }
            else {
                height = 1 + right->height;
            }
        }

    }
};
