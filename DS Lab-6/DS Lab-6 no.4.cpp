#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function to find the subset of an element u (uses path compression)
int find(Subset subsets[], int u) {
    if (subsets[u].parent != u)
        subsets[u].parent = find(subsets, subsets[u].parent);
    return subsets[u].parent;
}

// Function to do union of two subsets (uses union by rank)
void Union(Subset subsets[], int u, int v) {
    int rootU = find(subsets, u);
    int rootV = find(subsets, v);

    if (subsets[rootU].rank < subsets[rootV].rank) {
        subsets[rootU].parent = rootV;
    } else if (subsets[rootU].rank > subsets[rootV].rank) {
        subsets[rootV].parent = rootU;
    } else {
        subsets[rootV].parent = rootU;
        subsets[rootU].rank++;
    }
}

// Function to find the Minimum Spanning Tree using Kruskal's algorithm
void kruskal(vector<Edge>& edges, int V) {
    // Sort edges by increasing order of weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Allocate memory for creating V subsets
    Subset* subsets = new Subset[V];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> result; // To store the resultant MST

    for (Edge& edge : edges) {
        int u = find(subsets, edge.u);
        int v = find(subsets, edge.v);

        // If including this edge doesn't cause a cycle, include it in the result
        if (u != v) {
            result.push_back(edge);
            Union(subsets, u, v);
        }
    }

    // Print the contents of the MST
    cout << "Minimum Spanning Tree:" << endl;
    int mstWeight = 0;
    for (Edge& edge : result) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
        mstWeight += edge.weight;
    }
    cout << "Total weight of MST: " << mstWeight << endl;

    delete[] subsets; // Free the allocated memory
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);

    cout << "Enter the edges (u v weight):" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    kruskal(edges, V);

    return 0;
}
