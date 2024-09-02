#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Kosaraju {
private:
    int n;
    vector<vector<T>> adj, radj;
    vector<bool> visited;
    vector<int> order, component;

    void dfs1(int v) {
        visited[v] = true;
        for (T u : adj[v])
            if (!visited[u])
                dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v) {
        visited[v] = true;
        component.push_back(v);
        for (T u : radj[v])
            if (!visited[u])
                dfs2(u);
    }

public:
    Kosaraju(int n) : n(n), adj(n), radj(n), visited(n, false) {}

    void add(T u, T v) {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    vector<vector<int>> get() {
        fill(visited.begin(), visited.end(), false);
        for (int i = 0; i < n; ++i)
            if (!visited[i])
                dfs1(i);

        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            if (!visited[v]) {
                component.clear();
                dfs2(v);
                sccs.push_back(component);
            }
        }
        return sccs;
    }
}; // * Note: 0-based index

int main() {
    
}