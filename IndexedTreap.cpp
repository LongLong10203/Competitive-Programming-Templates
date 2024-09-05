#include <bits/stdc++.h>
using namespace std;

template<typename T>
class IndexedTreap {
    struct Node {
        T key;
        int priority, size;
        T sum, maxVal, minVal;
        T lazy; // For range updates
        Node *left, *right;
        Node(T k, int p) : key(k), priority(p), size(1), sum(k), maxVal(k), minVal(k), lazy(0), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    mt19937 rng;

    static int getSize(Node* t) {
        return t ? t->size : 0;
    }

    static T getSum(Node* t) {
        return t ? t->sum : 0;
    }

    static T getMaxVal(Node* t) {
        return t ? t->maxVal : numeric_limits<T>::lowest();
    }

    static T getMinVal(Node* t) {
        return t ? t->minVal : numeric_limits<T>::max();
    }

    static void updateNode(Node* t) {
        if (t) {
            t->size = 1 + getSize(t->left) + getSize(t->right);
            t->sum = t->key + getSum(t->left) + getSum(t->right);
            t->maxVal = max(t->key, max(getMaxVal(t->left), getMaxVal(t->right)));
            t->minVal = min(t->key, min(getMinVal(t->left), getMinVal(t->right)));
        }
    }

    static void applyLazy(Node* t) {
        if (t && t->lazy != 0) {
            t->key += t->lazy;
            t->sum += t->lazy * t->size;
            t->maxVal += t->lazy;
            t->minVal += t->lazy;
            if (t->left) t->left->lazy += t->lazy;
            if (t->right) t->right->lazy += t->lazy;
            t->lazy = 0;
        }
    }

    void split(Node* t, int index, Node*& l, Node*& r) {
        applyLazy(t);
        if (!t) {
            l = r = nullptr;
        } else if (index <= getSize(t->left)) {
            split(t->left, index, l, t->left);
            r = t;
        } else {
            split(t->right, index - getSize(t->left) - 1, t->right, r);
            l = t;
        }
        updateNode(t);
    }

    void merge(Node*& t, Node* l, Node* r) {
        applyLazy(l);
        applyLazy(r);
        if (!l || !r) {
            t = l ? l : r;
        } else if (l->priority > r->priority) {
            merge(l->right, l->right, r);
            t = l;
        } else {
            merge(r->left, l, r->left);
            t = r;
        }
        updateNode(t);
    }

    void insert(Node*& t, Node* it, int index) {
        applyLazy(t);
        if (!t) {
            t = it;
        } else if (it->priority > t->priority) {
            split(t, index, it->left, it->right);
            t = it;
        } else {
            if (index <= getSize(t->left)) {
                insert(t->left, it, index);
            } else {
                insert(t->right, it, index - getSize(t->left) - 1);
            }
        }
        updateNode(t);
    }

    void erase(Node*& t, int index) {
        applyLazy(t);
        if (!t) return;
        if (index == getSize(t->left)) {
            Node* temp = t;
            merge(t, t->left, t->right);
            delete temp;
        } else if (index < getSize(t->left)) {
            erase(t->left, index);
        } else {
            erase(t->right, index - getSize(t->left) - 1);
        }
        updateNode(t);
    }

    T rangeQuery(Node*& t, int left, int right, function<T(Node*)> queryFunc) {
        Node *L = nullptr, *M = nullptr, *R = nullptr;
        split(t, right + 1, M, R); // Split out the range [0, right]
        split(M, left, L, M);      // Split out the range [left, right]
        T result = queryFunc(M);   // Query the middle part
        merge(M, L, M);            // Merge left and middle
        merge(t, M, R);            // Merge the result back with the right part
        return result;
    }

    void rangeUpdate(Node*& t, int left, int right, T delta) {
        Node *L = nullptr, *M = nullptr, *R = nullptr;
        split(t, right + 1, M, R); // Split out the range [0, right]
        split(M, left, L, M);      // Split out the range [left, right]
        // Apply update to the middle part
        applyUpdate(M, delta);
        merge(M, L, M);            // Merge left and middle
        merge(t, M, R);            // Merge the result back with the right part
    }

    void applyUpdate(Node*& t, T delta) {
        if (t) {
            t->lazy += delta;
            applyLazy(t);
        }
    }

public:
    IndexedTreap() : root(nullptr), rng(chrono::steady_clock::now().time_since_epoch().count()) {}

    void insert(int index, T key) {
        Node* it = new Node(key, rng());
        insert(root, it, index);
    }

    void erase(int index) {
        erase(root, index);
    }

    void update(int left, int right, T delta) {
        rangeUpdate(root, left, right, delta);
    }

    T rangeSum(int left, int right) {
        return rangeQuery(root, left, right, [](Node* t) { return getSum(t); });
    }

    T rangeMax(int left, int right) {
        return rangeQuery(root, left, right, [](Node* t) { return getMaxVal(t); });
    }

    T rangeMin(int left, int right) {
        return rangeQuery(root, left, right, [](Node* t) { return getMinVal(t); });
    }

    int size() {
        return getSize(root);
    }
}; // * Note: 0-based index

int main() {
    
}