#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

// pair<weight, vertex>
typedef pair<int,int> Edge;

void primMST(int V, const vector<vector<Edge>>& adj) {
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);

    // Min-heap: (key, vertex)
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) 
            continue;
        inMST[u] = true;

        // Relax all edges from u
        for (const auto& e : adj[u]) {
            int weight = e.first;
            int v      = e.second;
            if (!inMST[v] && weight < key[v]) {
                key[v]    = weight;
                parent[v] = u;
                pq.push({weight, v});
            }
        }
    }

    // Print the MST edges and weights
    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        if (parent[i] != -1)
            cout << parent[i] << " - " << i << "\t" << key[i] << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin  >> V >> E;

    vector<vector<Edge>> adj(V);
    cout << "Enter edges as: source destination weight\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    primMST(V, adj);
    return 0;
}
