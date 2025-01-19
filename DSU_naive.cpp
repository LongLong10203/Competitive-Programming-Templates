#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> lomo;
    vector<int> sz;

public:
    DSU(int n) {
        lomo.resize(n);
        sz.resize(n, 1);
        iota(lomo.begin(), lomo.end(), 0);
    }

    int find(int u) {
        return lomo[u] == u ? u : lomo[u] = find(lomo[u]);
    }

    void unite(int u, int v) {
        int ru = find(u), rv = find(v);
        if (ru != rv) {
            // unite by size
            if (sz[ru] < sz[rv])
                swap(ru, rv);
            lomo[rv] = ru;
            sz[ru] += sz[rv];
        }
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    int size(int u) {
        return sz[find(u)];
    }
}; // * 0-based index

int main() {
    
}