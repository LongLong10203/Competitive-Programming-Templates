#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
template<typename T>
class LazyRMQ {
private:
    int n;
    vector<T> tree, lazyAdd, lazySet;
    vector<bool> hasLazyAdd, hasLazySet;
 
    T combine(T left, T right) {
        return left + right;  // only min/max operations are supported
    }

    void push(int v, int tl, int tr) {
        if (hasLazySet[v]) {
            applySet(v * 2, tl, (tl + tr) / 2, lazySet[v]);
            applySet(v * 2 + 1, (tl + tr) / 2 + 1, tr, lazySet[v]);
            lazySet[v] = 0;
            hasLazySet[v] = false;
            lazyAdd[v] = 0;
            hasLazyAdd[v] = false;
        }
 
        if (hasLazyAdd[v]) {
            applyAdd(v * 2, tl, (tl + tr) / 2, lazyAdd[v]);
            applyAdd(v * 2 + 1, (tl + tr) / 2 + 1, tr, lazyAdd[v]);
            lazyAdd[v] = 0;
            hasLazyAdd[v] = false;
        }
    }
 
    void applyAdd(int v, int tl, int tr, T addVal) {
        tree[v] += addVal;
        if (tl != tr) {
            lazyAdd[v] += addVal;
            hasLazyAdd[v] = true;
        }
    }
 
    void applySet(int v, int tl, int tr, T setVal) {
        tree[v] = setVal;
        if (tl != tr) {
            lazySet[v] = setVal;
            hasLazySet[v] = true;
            lazyAdd[v] = 0;
            hasLazyAdd[v] = false;
        }
    }
 
    void build(const vector<T>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
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
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
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
            tree[v] = combine(tree[v * 2], tree[v * 2 + 1]);
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
    LazyRMQ(const vector<T>& arr) {
        n = arr.size();
        tree.resize(n * 4);
        lazyAdd.resize(n * 4, 0);
        lazySet.resize(n * 4, 0);
        hasLazyAdd.resize(n * 4, false);
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