#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void question3() {
    printf("\n\nMINIMUM SPANNING TREE (KRUSKAL'S)\n\n");
    
    int V = 7; // Vertices A, B, C, D, E, F, G (0-6)
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    // Graph edges from the image
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
    
    // Adjacency Matrix
    printf("Adjacency Matrix:\n   ");
    for (int i = 0; i < V; i++) printf("%3c", vertices[i]);
    printf("\n");
    
    int adjMatrix[7][7] = {0};
    for (int i = 0; i < E; i++) {
        adjMatrix[edges[i].src][edges[i].dest] = edges[i].weight;
        adjMatrix[edges[i].dest][edges[i].src] = edges[i].weight;
    }
    
    for (int i = 0; i < V; i++) {
        printf("%c: ", vertices[i]);
        for (int j = 0; j < V; j++) {
            printf("%3d", adjMatrix[i][j]);
        }
        printf("\n");
    }
    
    // Kruskal's Algorithm
    qsort(edges, E, sizeof(Edge), compareEdges);
    
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    
    Edge* result = (Edge*)malloc(V * sizeof(Edge));
    int e = 0;
    int totalCost = 0;
    
    printf("\nKruskal's Algorithm - Selected Edges:\n");
    for (int i = 0; i < E && e < V - 1; i++) {
        int x = find(subsets, edges[i].src);
        int y = find(subsets, edges[i].dest);
        
        if (x != y) {
            result[e++] = edges[i];
            printf("%c-%c: %d\n", vertices[edges[i].src], vertices[edges[i].dest], edges[i].weight);
            totalCost += edges[i].weight;
            unionSets(subsets, x, y);
        }
    }
    
    printf("\nTotal Minimum Cost (MST): %d\n", totalCost);
    free(subsets);
    free(result);
}

int main() {
    question3();
    return 0;
}