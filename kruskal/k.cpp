#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
};

// Compare edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Disjoint Set Union (Union-Find)
class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return false;

        if (rank[pu] < rank[pv]) {
            parent[pu] = pv;
        } else if (rank[pu] > rank[pv]) {
            parent[pv] = pu;
        } else {
            parent[pv] = pu;
            rank[pu]++;
        }
        return true;
    }
};

void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compare);
    DisjointSet ds(V);

    int totalWeight = 0;
    vector<Edge> result;

    for (const Edge& e : edges) {
        if (ds.unite(e.u, e.v)) {
            result.push_back(e);
            totalWeight += e.weight;
        }
    }

    cout << "\nMinimum Spanning Tree:\n";
    cout << "Edge\tWeight\n";
    for (const Edge& e : result) {
        cout << e.u << " - " << e.v << "\t" << e.weight << "\n";
    }
    cout << "Total Weight: " << totalWeight << "\n";
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges as: source destination weight\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    kruskalMST(V, edges);
    return 0;
}
/*
Enter number of vertices and edges: 5 7
Enter edges as: source destination weight
0 1 2
0 3 6
1 2 3
1 3 8
1 4 5
2 4 7
3 4 9
*/