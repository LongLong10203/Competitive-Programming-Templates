#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DSU {
    unordered_map<T, T> parent;
    unordered_map<T, int> rank;
    unordered_map<T, int> sz;

public:
    DSU() = default;

    DSU(const vector<T>& elements) {
        for (const T& elem : elements) {
            parent[elem] = elem;
            rank[elem] = 1;
            sz[elem] = 1;
        }
    }

    T find(T u) {
        if (parent.find(u) == parent.end()) { // init
            parent[u] = u;
            sz[u] = 1;
            rank[u] = 1;
        }
        if (parent[u] != u)
            parent[u] = find(parent[u]); // path compression
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
};

int main() {
    
}