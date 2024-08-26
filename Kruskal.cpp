#include <bits/stdc++.h>
using namespace std;

class KruskalMST {
public:
    struct Edge {
        int src, dest, weight;
    };

private:
    vector<Edge> edges;
    int V;

    struct DSU {
        vector<int> parent, rank;

        DSU(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }

        int find(int u) {
            if (u != parent[u])
                parent[u] = find(parent[u]);
            return parent[u];
        }

        void unite(int u, int v) {
            int rootU = find(u);
            int rootV = find(v);
            if (rootU != rootV) {
                if (rank[rootU] < rank[rootV]) {
                    parent[rootU] = rootV;
                } else if (rank[rootU] > rank[rootV]) {
                    parent[rootV] = rootU;
                } else {
                    parent[rootV] = rootU;
                    rank[rootU]++;
                }
            }
        }
    };

    static bool compareEdges(const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    }

public:
    KruskalMST(int vertices) : V(vertices) {}

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    vector<Edge> query() {
        vector<Edge> result;
        sort(edges.begin(), edges.end(), compareEdges);
        DSU dsu(V);
        for (Edge &edge : edges) {
            if (dsu.find(edge.src) != dsu.find(edge.dest)) {
                result.push_back(edge);
                dsu.unite(edge.src, edge.dest);
            }
        }
        return result;
    }
}; // * Note: 0-based index 

int main() {
    
}