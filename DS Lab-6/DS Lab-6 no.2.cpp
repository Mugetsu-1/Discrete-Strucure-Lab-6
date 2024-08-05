#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];
int degree[MAX];
bool visited[MAX];
int n;

// Function to initialize the graph
void init_graph(int vertices) {
    n = vertices;
    for (int i = 0; i < MAX; i++) {
        degree[i] = 0;
        visited[i] = false;
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = 0;
        }
    }
}

// Function to add an edge to the graph
void add_edge(int u, int v) {
    graph[u][v]++;
    graph[v][u]++;
    degree[u]++;
    degree[v]++;
}

// Function to perform DFS
void dfs(int v) {
    visited[v] = true;
    for (int u = 0; u < n; u++) {
        if (graph[v][u] && !visited[u]) {
            dfs(u);
        }
    }
}

// Function to check if all non-zero degree vertices are connected
bool is_connected() {
    int i, start_vertex = -1;
    for (i = 0; i < n; i++) {
        if (degree[i] > 0) {
            start_vertex = i;
            break;
        }
    }

    if (start_vertex == -1) {
        return true;
    }

    dfs(start_vertex);

    for (i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i]) {
            return false;
        }
    }

    return true;
}

// Function to find Euler path or circuit
void find_euler(int u) {
    for (int v = 0; v < n; v++) {
        while (graph[u][v]) {
            graph[u][v]--;
            graph[v][u]--;
            find_euler(v);
        }
    }
    printf("%d ", u);
}

int main() {
    int vertices, edges, u, v, odd_count = 0;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    init_graph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    if (!is_connected()) {
        printf("The graph is not connected.\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            odd_count++;
        }
    }

    if (odd_count == 0) {
        printf("The graph has an Euler circuit:\n");
        find_euler(0);
    } else if (odd_count == 2) {
        printf("The graph has an Euler path:\n");
        for (int i = 0; i < n; i++) {
            if (degree[i] % 2 != 0) {
                find_euler(i);
                break;
            }
        }
    } else {
        printf("The graph has neither an Euler path nor an Euler circuit.\n");
    }

    return 0;
}

