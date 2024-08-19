#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void dijkstra(int source, int destination, const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == destination) break;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[destination] == INF) {
        cout << "No path between " << source << " and " << destination << endl;
    } else {
        cout << "Shortest distance from " << source << " to " << destination << " is " << dist[destination] << endl;
        cout << "Path: ";
        vector<int> path;
        for (int v = destination; v != -1; v = parent[v]) path.push_back(v);
        for (int i = path.size() - 1; i >= 0; i--) cout << path[i] << (i > 0 ? " -> " : "\n");
    }
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n);

    cout << "Enter the edges (u v weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w); // Remove this line for directed graphs
    }

    int source, destination;
    cout << "Enter the source and destination vertices: ";
    cin >> source >> destination;

    dijkstra(source, destination, graph);

    return 0;
}
