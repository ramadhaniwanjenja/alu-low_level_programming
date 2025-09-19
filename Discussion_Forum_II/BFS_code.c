#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int visited[MAX];
int adj[MAX][MAX];
int queue[MAX];
int front = -1, rear = -1;
int n;

void enqueue(int v) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

void bfs(int start) {
    visited[start] = 1;
    enqueue(start);

    while (front <= rear) {
        int v = dequeue();
        printf("%d ", v);

        for (int i = 1; i <= n; i++) {
            if (adj[v][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
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

    printf("BFS starting from 1: ");
    bfs(1);
    return 0;
}
