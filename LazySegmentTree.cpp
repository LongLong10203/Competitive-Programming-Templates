#include <bits/stdc++.h>
using namespace std;

template<typename T>
class LazySegmentTree {
private:
    int n;
    vector<T> tree, lazyAdd, lazySet;
    vector<bool> hasLazySet;

    void build(const vector<T>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    void push(int v, int tl, int tr) {
        int tm = (tl + tr) / 2;
        if (hasLazySet[v]) {
            applySet(v * 2, tl, tm, lazySet[v]);
            applySet(v * 2 + 1, tm + 1, tr, lazySet[v]);
            hasLazySet[v] = false;
            lazySet[v] = 0;
        }
        if (lazyAdd[v] != 0) {
            applyAdd(v * 2, tl, tm, lazyAdd[v]);
            applyAdd(v * 2 + 1, tm + 1, tr, lazyAdd[v]);
            lazyAdd[v] = 0;
        }
    }

    void applyAdd(int v, int tl, int tr, T addVal) {
        tree[v] += addVal * (tr - tl + 1);
        if (tl != tr) {
            lazyAdd[v] += addVal;
        }
    }

    void applySet(int v, int tl, int tr, T setVal) {
        tree[v] = setVal * (tr - tl + 1);
        if (tl != tr) {
            lazySet[v] = setVal;
            hasLazySet[v] = true;
            lazyAdd[v] = 0;  // clear pending add
        }
    }

    void updateAdd(int v, int tl, int tr, int l, int r, T addVal) {
        if (l > r) return;
        if (l == tl && r == tr) {
            applyAdd(v, tl, tr, addVal);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            updateAdd(v * 2, tl, tm, l, min(r, tm), addVal);
            updateAdd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addVal);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    void updateSet(int v, int tl, int tr, int l, int r, T setVal) {
        if (l > r) return;
        if (l == tl && r == tr) {
            applySet(v, tl, tr, setVal);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            updateSet(v * 2, tl, tm, l, min(r, tm), setVal);
            updateSet(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, setVal);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    T query(int idx, int l, int r, int left, int right) {
        push(idx, l, r);
        if (left == l && right == r)
            return tree[idx];
        int mid = (l + r) / 2;
        if (right <= mid)
            return query(2 * idx, l, mid, left, right);
        else if (left > mid)
            return query(2 * idx + 1, mid + 1, r, left, right);
        else
            return query(2 * idx, l, mid, left, mid) + 
                   query(2 * idx + 1, mid + 1, r, mid + 1, right);
    }

public:
    LazySegmentTree(const vector<T>& arr) {
        n = arr.size();
        tree.resize(n * 4);
        lazyAdd.resize(n * 4, 0);
        lazySet.resize(n * 4, 0);
        hasLazySet.resize(n * 4, false);
        build(arr, 1, 0, n - 1);
    }

    void updateAdd(int l, int r, T addVal) {
        updateAdd(1, 0, n - 1, l, r, addVal);
    }

    void updateSet(int l, int r, T setVal) {
        updateSet(1, 0, n - 1, l, r, setVal);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    
}