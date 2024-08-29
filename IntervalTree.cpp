#include <bits/stdc++.h>
using namespace std;

template <typename T>
class IntervalTree {
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

    Node* deleteNode(Node* node, T low, T high) {
        if (!node) return nullptr;

        if (low < node->low) node->left = deleteNode(node->left, low, high);
        else if (low > node->low) node->right = deleteNode(node->right, low, high);
        else if (high == node->high) {
            if (!node->left) {
                Node* right = node->right;
                delete node;
                return right;
            }
            else if (!node->right) {
                Node* left = node->left;
                delete node;
                return left;
            }

            Node* minNode = findMin(node->right);
            node->low = minNode->low;
            node->high = minNode->high;
            node->right = deleteNode(node->right, minNode->low, minNode->high);
        }
        else {
            node->right = deleteNode(node->right, low, high);
        }

        node->max = max(node->high, max(getMax(node->left), getMax(node->right)));
        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
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

    T getMax(Node* node) {
        return node ? node->max : numeric_limits<T>::min();
    }

public:
    IntervalTree() : root(nullptr) {}

    void insert(T low, T high) {
        root = insert(root, low, high);
    }

    void remove(T low, T high) {
        root = deleteNode(root, low, high);
    }

    pair<T, T> search(T low, T high) {
        Node* res = searchOverlap(root, low, high);
        if (res) return {res->low, res->high};
        return {numeric_limits<T>::min(), numeric_limits<T>::min()};
    }

    bool overlap(T low, T high) {
        return searchOverlap(root, low, high) != nullptr;
    }
};

int main() {
    
}