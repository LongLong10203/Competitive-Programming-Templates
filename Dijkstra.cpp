#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
const int INF = numeric_limits<int>::max();

void dijkstra(int src, const vector<vector<pii>>& graph, vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, INF);
    dist[src] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    
}