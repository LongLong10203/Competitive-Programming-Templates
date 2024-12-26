#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree { // specially designed to solve https://judge.hkoi.org/task/01010 Diamond Chain
private:
    struct Node {
        T maxSum, prefixSum, suffixSum, totalSum;

        Node(T value = 0) {
            totalSum = value;
            prefixSum = suffixSum = maxSum = max(T(0), value);
        }
    };

    vector<Node> tree;
    vector<T> data;
    int n;

    Node combine(Node left, Node right) {
        Node res;
        res.totalSum = left.totalSum + right.totalSum;
        res.prefixSum = max(left.prefixSum, left.totalSum + right.prefixSum);
        res.suffixSum = max(right.suffixSum, right.totalSum + left.suffixSum);
        res.maxSum = max({left.maxSum, right.maxSum, left.suffixSum + right.prefixSum});
        return res;
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx] = Node(data[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(2 * idx, l, mid);
        build(2 * idx + 1, mid + 1, r);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    void update(int idx, int l, int r, int pos, T val) {
        if (l == r) {
            tree[idx] = Node(val);
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(2 * idx, l, mid, pos, val);
        else
            update(2 * idx + 1, mid + 1, r, pos, val);
        tree[idx] = combine(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node query(int idx, int l, int r, int left, int right) {
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
    SegmentTree(const vector<T>& input_data) {
        data = input_data;
        n = data.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    void update(int pos, T val) {
        update(1, 0, n - 1, pos, val);
    }

    T query(int l, int r) {
        Node result = query(1, 0, n - 1, l, r);
        return result.maxSum;
    }
}; // * Note: 0-based index

int main() {
    
}