#include <bits/stdc++.h>
using namespace std;

template <typename T>
class IntervalTree { // experimental
private:
    struct Node {
        T low, high, max;
        Node *left, *right;
        Node(T l, T h) : low(l), high(h), max(h), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, T low, T high) {
        if (!node) return new Node(low, high);

        if (low < node->low) node->left = insert(node->left, low, high);
        else node->right = insert(node->right, low, high);

        node->max = max(node->max, high);
        return node;
    }

    bool doOverlap(T l1, T h1, T l2, T h2) {
        return l1 <= h2 && l2 <= h1;
    }

    Node* searchOverlap(Node* node, T low, T high) {
        if (!node) return nullptr;
        if (doOverlap(node->low, node->high, low, high)) return node;

        if (node->left && node->left->max >= low) return searchOverlap(node->left, low, high);
        return searchOverlap(node->right, low, high);
    }

public:
    IntervalTree() : root(nullptr) {}

    void insert(T low, T high) {
        root = insert(root, low, high);
    }

    bool overlap(T low, T high) {
        return searchOverlap(root, low, high) != nullptr;
    }
};

int main() {
    
}