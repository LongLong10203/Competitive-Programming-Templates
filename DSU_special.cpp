#include <bits/stdc++.h>
using namespace std;

template <typename T>
class DSU {
    unordered_map<T, T> lomo;
    unordered_map<T, int> sz;

public:
    DSU() = default;

    T find(T u) {
        if (lomo.find(u) == lomo.end()) { // init
            lomo[u] = u;
            sz[u] = 1;
        }
        return lomo[u] == u ? u : lomo[u] = find(lomo[u]);
    }

    void unite(T u, T v) {
        T ru = find(u), rv = find(v);
        if (ru != rv) {
            // union by size
            if (sz[ru] < sz[rv])
                swap(ru, rv);
            lomo[rv] = ru;
            sz[ru] += sz[rv];
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