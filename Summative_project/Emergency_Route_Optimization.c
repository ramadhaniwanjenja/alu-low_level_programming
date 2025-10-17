#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 20
#define INF INT_MAX
#define NODE_NAME_LEN 30

typedef struct Edge {
    int dest;
    int weight;
    struct Edge *next;
} Edge;

typedef struct {
    char name[NODE_NAME_LEN];
    Edge *adj_list;
} Node;

typedef struct {
    Node nodes[MAX_NODES];
    int node_count;
} Graph;

Graph graph = {{}, 0};

int find_node_index(const char *name) {
    for (int i = 0; i < graph.node_count; i++) {
        if (strcmp(graph.nodes[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int add_node(const char *name) {
    int idx = find_node_index(name);
    if (idx != -1) {
        return idx;
    }
    
    strcpy(graph.nodes[graph.node_count].name, name);
    graph.nodes[graph.node_count].adj_list = NULL;
    return graph.node_count++;
}

void add_edge_directed(int from, int to, int weight) {
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->dest = to;
    new_edge->weight = weight;
    new_edge->next = graph.nodes[from].adj_list;
    graph.nodes[from].adj_list = new_edge;
}

void add_bidirectional_edge(const char *node1, const char *node2, int weight) {
    int idx1 = add_node(node1);
    int idx2 = add_node(node2);
    add_edge_directed(idx1, idx2, weight);
    add_edge_directed(idx2, idx1, weight);
}

int min_distance(int dist[], int visited[]) {
    int min = INF, min_index = -1;
    for (int i = 0; i < graph.node_count; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_path(int parent[], int dest, int path[], int *path_len) {
    if (parent[dest] == -1) {
        path[(*path_len)++] = dest;
        return;
    }
    print_path(parent, parent[dest], path, path_len);
    path[(*path_len)++] = dest;
}

void dijkstra(int start, int destination) {
    int dist[MAX_NODES];
    int visited[MAX_NODES] = {0};
    int parent[MAX_NODES];
    
    for (int i = 0; i < graph.node_count; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;
    
    for (int count = 0; count < graph.node_count - 1; count++) {
        int u = min_distance(dist, visited);
        if (u == -1) break;
        
        visited[u] = 1;
        
        Edge *edge = graph.nodes[u].adj_list;
        while (edge) {
            int v = edge->dest;
            if (!visited[v] && dist[u] != INF && 
                dist[u] + edge->weight < dist[v]) {
                dist[v] = dist[u] + edge->weight;
                parent[v] = u;
            }
            edge = edge->next;
        }
    }
    
    printf("\n=== Route Optimization Result ===\n");
    printf("From: %s\n", graph.nodes[start].name);
    printf("To: %s\n", graph.nodes[destination].name);
    
    if (dist[destination] == INF) {
        printf("\nNo route available!\n");
        return;
    }
    
    int path[MAX_NODES];
    int path_len = 0;
    print_path(parent, destination, path, &path_len);
    
    printf("\nOptimal Path:\n");
    for (int i = 0; i < path_len; i++) {
        printf("%s", graph.nodes[path[i]].name);
        if (i < path_len - 1) {
            printf(" -> ");
        }
    }
    printf("\n\nTotal Travel Time: %d minutes\n\n", dist[destination]);
}

void build_network() {
    printf("Building smart city road network...\n");
    add_bidirectional_edge("Dispatch Center", "Sector A", 10);
    add_bidirectional_edge("Dispatch Center", "Sector D", 30);
    add_bidirectional_edge("Sector A", "Sector B", 10);
    add_bidirectional_edge("Sector B", "Emergency Site", 15);
    add_bidirectional_edge("Sector D", "Emergency Site", 5);
    add_bidirectional_edge("Sector B", "Junction C", 3);
    add_bidirectional_edge("Junction C", "Sector E", 6);
    add_bidirectional_edge("Sector E", "Emergency Site", 4);
    printf("Network established with %d locations.\n\n", graph.node_count);
}

void free_graph() {
    for (int i = 0; i < graph.node_count; i++) {
        Edge *current = graph.nodes[i].adj_list;
        while (current) {
            Edge *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    printf("=== Emergency Route Optimization System ===\n\n");
    build_network();
    
    printf("Available locations:\n");
    for (int i = 0; i < graph.node_count; i++) {
        printf("%d. %s\n", i + 1, graph.nodes[i].name);
    }
    
    char start_location[NODE_NAME_LEN];
    printf("\nEnter starting location (e.g., 'Dispatch Center'): ");
    fgets(start_location, NODE_NAME_LEN, stdin);
    start_location[strcspn(start_location, "\n")] = 0;
    
    int start_idx = find_node_index(start_location);
    int dest_idx = find_node_index("Emergency Site");
    
    if (start_idx == -1) {
        printf("Error: Starting location not found in network.\n");
        free_graph();
        return 1;
    }
    
    dijkstra(start_idx, dest_idx);
    
    free_graph();
    return 0;
}
