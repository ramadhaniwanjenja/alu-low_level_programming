#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

void question5() {
    printf("\n\nBELLMAN-FORD - SHORTEST PATH \n\n");
    
    int V = 7;
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    Edge edges[] = {
        {0, 1, 6},   // A-B: 6
        {0, 6, 15},  // A-G: 15
        {1, 2, 11},  // B-C: 11
        {1, 3, 5},   // B-D: 5
        {2, 3, 17},  // C-D: 17
        {2, 5, 9},   // C-F: 9
        {2, 6, 25},  // C-G: 25
        {3, 4, 22},  // D-E: 22
        {4, 5, 10},  // E-F: 10
        {5, 6, 12}   // F-G: 12
    };
    int E = 10;
    
    // Make edges bidirectional
    Edge allEdges[20];
    for (int i = 0; i < E; i++) {
        allEdges[2*i] = edges[i];
        allEdges[2*i+1].src = edges[i].dest;
        allEdges[2*i+1].dest = edges[i].src;
        allEdges[2*i+1].weight = edges[i].weight;
    }
    E = 20;
    
    int *dist = (int*)malloc(V * sizeof(int));
    int *parent = (int*)malloc(V * sizeof(int));
    
    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[0] = 0; // Source is A (index 0)
    
    // Bellman-Ford Algorithm
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = allEdges[j].src;
            int v = allEdges[j].dest;
            int weight = allEdges[j].weight;
            
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }
    
    // Print results
    printf("Shortest paths from City A (warehouse) to all cities:\n\n");
    for (int i = 0; i < V; i++) {
        printf("City %c: ", vertices[i]);
        if (dist[i] == INF) {
            printf("No path\n");
        } else {
            printf("Cost = %d, Path: ", dist[i]);
            
            // Reconstruct path
            int *path = (int*)malloc(V * sizeof(int));
            int pathLen = 0;
            int current = i;
            
            while (current != -1) {
                path[pathLen++] = current;
                current = parent[current];
            }
            
            for (int j = pathLen - 1; j >= 0; j--) {
                printf("%c", vertices[path[j]]);
                if (j > 0) printf(" -> ");
            }
            printf("\n");
            free(path);
        }
    }
    // Free dynamically allocated memory
    free(dist);
    free(parent);
}
int main() {
    question5();
    return 0;
}
