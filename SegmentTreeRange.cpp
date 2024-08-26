#include <bits/stdc++.h>
using namespace std;

template<typename T>
class SegmentTree {
private:
    vector<int> tree;
    vector<T> arr;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = 0;
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void updateRange(int node, int start, int end, T A, T B) {
        if (start == end) {
            tree[node] = (arr[start] >= A && arr[start] <= B) ? 1 : 0;
        } else {
            int mid = (start + end) / 2;
            updateRange(2 * node, start, mid, A, B);
            updateRange(2 * node + 1, mid + 1, end, A, B);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void updateSet(int idx, int start, int end, int pos, T v) {
        if (start == end) {
            arr[start] = v;
            tree[idx] = (arr[start] >= v && arr[start] <= v) ? 1 : 0;
        } else {
            int mid = (start + end) / 2;
            if (pos <= mid)
                updateSet(2 * idx, start, mid, pos, v);
            else
                updateSet(2 * idx + 1, mid + 1, end, pos, v);
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }

    void updateAdd(int idx, int start, int end, int pos, T v) {
        if (start == end) {
            arr[start] += v;
            tree[idx] = (arr[start] >= arr[start] && arr[start] <= arr[start]) ? 1 : 0;
        } else {
            int mid = (start + end) / 2;
            if (pos <= mid)
                updateAdd(2 * idx, start, mid, pos, v);
            else
                updateAdd(2 * idx + 1, mid + 1, end, pos, v);
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
        }
    }

    T combine(T left, T right) {
        return left + right;
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

public:
    SegmentTree(vector<T>& input) : arr(input) {
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    T query(int L, int R, T A, T B) {
        updateRange(1, 0, n - 1, A, B);
        return query(1, 0, n - 1, L, R);
    }

    void set(int pos, T v) {
        updateSet(1, 0, n - 1, pos, v);
    }

    void add(int pos, T v) {
        updateAdd(1, 0, n - 1, pos, v);
    }
};

int main() {
    
}