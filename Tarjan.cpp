#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Tarjan {
    int n, index;
    vector<int> idx, low, inStack;
    stack<int> st;
    vector<vector<int>> adj;
    vector<vector<int>> sccs;

    void dfs(int u) {
        idx[u] = low[u] = index++;
        st.push(u);
        inStack[u] = 1;

        for (T v : adj[u]) {
            if (idx[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], idx[v]);
            }
        }

        if (low[u] == idx[u]) {
            vector<int> scc;
            int v;
            do {
                v = st.top(); st.pop();
                inStack[v] = 0;
                scc.push_back(v);
            } while (u != v);
            sccs.push_back(scc);
        }
    }

public:
    Tarjan(int n) : n(n), index(0), adj(n) {
        idx.assign(n, -1);
        low.assign(n, -1);
        inStack.assign(n, 0);
    }

    void add(T u, T v) {
        adj[u].push_back(v);
    }

    vector<vector<int>> get() {
        for (int i = 0; i < n; ++i)
            if (idx[i] == -1)
                dfs(i);
        return sccs;
    }
}; // * Note: 0-based index

int main() {
    
}