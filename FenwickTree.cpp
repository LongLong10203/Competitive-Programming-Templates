#include <bits/stdc++.h>
using namespace std;
 
template <typename T>
class FenwickTree {
public:
    FenwickTree() : n(0) {}

    FenwickTree(const vector<T>& list) : n(list.size()), tree(n + 1, 0) {
        for (int i = 0; i < n; ++i)
            tree[i + 1] = list[i];
        for (int i = 1; i <= n; ++i) {
            int j = i + (i & -i);
            if (j <= n) tree[j] += tree[i];
        }
    }

    T query(int l, int r) const {
        return prefix_query(r) - (l > 0 ? prefix_query(l - 1) : 0);
    }

    void add(int idx, T val) {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] += val;
    }

    void set(int idx, T val) {
        T current_val = get(idx);
        T diff = val - current_val;
        add(idx, diff);
    }

    T get(int idx) const {
        return query(idx, idx);
    }

private:
    int n;
    vector<T> tree;

    T prefix_query(int idx) const {
        T res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res += tree[idx];
        return res;
    }
}; // * Note: 0-based index

int main() {
    
}