#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int visited[MAX];
int adj[MAX][MAX];
int n;

void dfs(int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 1; i <= n; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int edges, v1, v2;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &v1, &v2);
        adj[v1][v2] = 1;
        adj[v2][v1] = 1; // undirected graph
    }

    for (int i = 1; i <= n; i++) visited[i] = 0;

    printf("DFS starting from 1: ");
    dfs(1);
    return 0;
}