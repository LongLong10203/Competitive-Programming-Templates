#include <bits/stdc++.h>
using namespace std;

class Kosaraju {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    void fillOrder(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (int i : adj[v])
            if (!visited[i])
                fillOrder(i, visited, Stack);
        Stack.push(v);
    }

    void DFSUtil(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (int i : adj[v])
            if (!visited[i])
                DFSUtil(i, visited, component);
    }

    Kosaraju getTranspose() {
        Kosaraju g(V);
        for (int v = 0; v < V; v++) {
            for (int i : adj[v]) {
                g.adj[i].push_back(v);
            }
        }
        return g;
    }

public:
    Kosaraju(int V) {
        this->V = V;
        adj.resize(V);
    }

    void add(int v, int w) {
        adj[v].push_back(w);
    }

    vector<vector<int>> get() {
        stack<int> Stack;
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
            if (!visited[i])
                fillOrder(i, visited, Stack);
        Kosaraju gr = getTranspose();
        fill(visited.begin(), visited.end(), false);
        vector<vector<int>> sccs;
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            if (!visited[v]) {
                vector<int> component;
                gr.DFSUtil(v, visited, component);
                sccs.push_back(component);
            }
        }
        return sccs;
    }
}; // * Note: 0-based index

int main() {
    
}