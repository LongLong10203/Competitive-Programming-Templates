#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree {
private:
    vector<T> tree, data;
    int n;

    T combine(T left, T right) {
        return left + right;  // modify this
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = data[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    T query(int idx, int l, int r, int left, int right) {
        if (left == l && right == r)
            return tree[idx];
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

    void update(int idx, int l, int r, int pos, T val) {
        if (l == r) {
            tree[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(2 * idx, l, mid, pos, val);
        else
            update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

public:
    SegmentTree(const vector<T>& input_data) {
        data = input_data;
        n = data.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void update(int pos, T val) {
        update(1, 0, n - 1, pos, val);
    }

    T query(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
}; // * Note: 0-based index

int main() {
    
}