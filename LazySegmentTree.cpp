#include <bits/stdc++.h>
using namespace std;

template <typename T>
class LazySegmentTree {
private:
    struct Node {
        T sum, min, max, lazySet, lazyAdd;
        bool toSet;
        Node() : sum(0), min(numeric_limits<T>::max()), max(numeric_limits<T>::min()), lazySet(0), lazyAdd(0), toSet(false) {}
    };

    vector<Node> tree;
    int n;

    void build(const vector<T>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].sum = tree[v].min = tree[v].max = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v*2, tl, tm);
            build(arr, v*2+1, tm+1, tr);
            merge(v);
        }
    }

    void applySet(int v, int tl, int tr, T value) {
        tree[v].sum = value * (tr - tl + 1);
        tree[v].min = tree[v].max = value;
        tree[v].lazySet = value;
        tree[v].lazyAdd = 0;
        tree[v].toSet = true;
    }

    void applyAdd(int v, int tl, int tr, T value) {
        tree[v].sum += value * (tr - tl + 1);
        tree[v].min += value;
        tree[v].max += value;
        if (tree[v].toSet) {
            tree[v].lazySet += value;
        } else {
            tree[v].lazyAdd += value;
        }
    }

    void push(int v, int tl, int tr) {
        if (tree[v].toSet) {
            int tm = (tl + tr) / 2;
            applySet(v*2, tl, tm, tree[v].lazySet);
            applySet(v*2+1, tm+1, tr, tree[v].lazySet);
            tree[v].toSet = false;
        }
        if (tree[v].lazyAdd != 0) {
            int tm = (tl + tr) / 2;
            applyAdd(v*2, tl, tm, tree[v].lazyAdd);
            applyAdd(v*2+1, tm+1, tr, tree[v].lazyAdd);
            tree[v].lazyAdd = 0;
        }
    }

    void merge(int v) {
        tree[v].sum = tree[v*2].sum + tree[v*2+1].sum;
        tree[v].min = min(tree[v*2].min, tree[v*2+1].min);
        tree[v].max = max(tree[v*2].max, tree[v*2+1].max);
    }

    void updateSet(int v, int tl, int tr, int l, int r, T value) {
        if (l > r) return;
        if (l == tl && r == tr) {
            applySet(v, tl, tr, value);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            updateSet(v*2, tl, tm, l, min(r, tm), value);
            updateSet(v*2+1, tm+1, tr, max(l, tm+1), r, value);
            merge(v);
        }
    }

    void updateAdd(int v, int tl, int tr, int l, int r, T value) {
        if (l > r) return;
        if (l == tl && r == tr) {
            applyAdd(v, tl, tr, value);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            updateAdd(v*2, tl, tm, l, min(r, tm), value);
            updateAdd(v*2+1, tm+1, tr, max(l, tm+1), r, value);
            merge(v);
        }
    }

    T querySum(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l <= tl && tr <= r) {
            return tree[v].sum;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return querySum(v*2, tl, tm, l, min(r, tm)) + querySum(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

    T queryMin(int v, int tl, int tr, int l, int r) {
        if (l > r) return numeric_limits<T>::max();
        if (l <= tl && tr <= r) {
            return tree[v].min;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return min(queryMin(v*2, tl, tm, l, min(r, tm)), queryMin(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

    T queryMax(int v, int tl, int tr, int l, int r) {
        if (l > r) return numeric_limits<T>::min();
        if (l <= tl && tr <= r) {
            return tree[v].max;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return max(queryMax(v*2, tl, tm, l, min(r, tm)), queryMax(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    LazySegmentTree(const vector<T>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void updateSet(int l, int r, T value) {
        updateSet(1, 0, n - 1, l, r, value);
    }

    void updateAdd(int l, int r, T value) {
        updateAdd(1, 0, n - 1, l, r, value);
    }

    T querySum(int l, int r) {
        return querySum(1, 0, n - 1, l, r);
    }

    T queryMin(int l, int r) {
        return queryMin(1, 0, n - 1, l, r);
    }

    T queryMax(int l, int r) {
        return queryMax(1, 0, n - 1, l, r);
    }
};

int main() {
    
}