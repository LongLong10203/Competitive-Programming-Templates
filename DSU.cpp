#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DSU {
    vector<T> parent;
    vector<int> rank;
    vector<int> sz;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        sz.resize(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    T find(T u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    void unite(T u, T v) {
        T rootU = find(u);
        T rootV = find(v);
        if (rootU != rootV) {
            // unite by rank
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
                sz[rootU] += sz[rootV];
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
                sz[rootV] += sz[rootU];
            } else {
                parent[rootV] = rootU;
                sz[rootU] += sz[rootV];
                rank[rootU]++;
            }
        }
    }

    bool same(T u, T v) {
        return find(u) == find(v);
    }

    int size(T u) {
        return sz[find(u)];
    }
}; // * 0-based index

int main() {
    
}