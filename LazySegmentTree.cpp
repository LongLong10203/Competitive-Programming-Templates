#include <bits/stdc++.h>
using namespace std;

template<typename T>
class LazySegmentTree {
private:
    int n;
    vector<T> tree, lazyAdd, lazySet;
    vector<bool> hasLazySet;

    T combine(T left, T right) {
        return left + right; // only plus operation is supported
    }

    void push(int idx, int l, int r) {
        if (hasLazySet[idx]) {
            applySet(idx * 2, l, (l + r) / 2, lazySet[idx]);
            applySet(idx * 2 + 1, (l + r) / 2 + 1, r, lazySet[idx]);
            lazySet[idx] = 0;
            hasLazySet[idx] = false;
        }

        if (lazyAdd[idx] != 0) {
            applyAdd(idx * 2, l, (l + r) / 2, lazyAdd[idx]);
            applyAdd(idx * 2 + 1, (l + r) / 2 + 1, r, lazyAdd[idx]);
            lazyAdd[idx] = 0;
        }
    }

    void applyAdd(int idx, int l, int r, T addVal) {
        tree[idx] += addVal * (r - l + 1);
        if (l != r) {
            lazyAdd[idx] += addVal;
        }
    }

    void applySet(int idx, int l, int r, T setVal) {
        tree[idx] = setVal * (r - l + 1);
        if (l != r) {
            lazySet[idx] = setVal;
            hasLazySet[idx] = true;
            lazyAdd[idx] = 0;
        }
    }

    void build(const vector<T>& arr, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l];
        } else {
            int mid = (l + r) / 2;
            build(arr, idx * 2, l, mid);
            build(arr, idx * 2 + 1, mid + 1, r);
            tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    void updateAdd(int idx, int l, int r, int left, int right, T addVal) {
        if (left > right) return;
        if (left == l && right == r) {
            applyAdd(idx, l, r, addVal);
        } else {
            push(idx, l, r);
            int mid = (l + r) / 2;
            updateAdd(idx * 2, l, mid, left, min(right, mid), addVal);
            updateAdd(idx * 2 + 1, mid + 1, r, max(left, mid + 1), right, addVal);
            tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    void updateSet(int idx, int l, int r, int left, int right, T setVal) {
        if (left > right) return;
        if (left == l && right == r) {
            applySet(idx, l, r, setVal);
        } else {
            push(idx, l, r);
            int mid = (l + r) / 2;
            updateSet(idx * 2, l, mid, left, min(right, mid), setVal);
            updateSet(idx * 2 + 1, mid + 1, r, max(left, mid + 1), right, setVal);
            tree[idx] = combine(tree[idx * 2], tree[idx * 2 + 1]);
        }
    }

    T query(int idx, int l, int r, int left, int right) {
        if (left == l && right == r)
            return tree[idx];
        
        push(idx, l, r);
        
        int mid = (l + r) / 2;
        
        if (right <= mid)
            return query(2 * idx, l, mid, left, right);
        else if (left > mid)
            return query(2 * idx + 1, mid + 1, r, left, right);
        else
            return combine(
                query(2 * idx, l, mid, left, mid),
                query(2 * idx + 1, mid + 1, r, mid + 1, right)
            );
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