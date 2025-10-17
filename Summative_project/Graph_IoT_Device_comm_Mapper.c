#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEVICES 50
#define DEVICE_ID_LEN 10

typedef struct EdgeNode {
    int dest_index;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    char device_id[DEVICE_ID_LEN];
    EdgeNode *adj_list;
} Device;

typedef struct {
    Device devices[MAX_DEVICES];
    int device_count;
    int adj_matrix[MAX_DEVICES][MAX_DEVICES];
} Graph;

Graph graph = {{}, 0, {{0}}};

int find_device_index(const char *device_id) {
    for (int i = 0; i < graph.device_count; i++) {
        if (strcmp(graph.devices[i].device_id, device_id) == 0) {
            return i;
        }
    }
    return -1;
}

int add_device(const char *device_id) {
    int index = find_device_index(device_id);
    if (index != -1) {
        return index;
    }
    
    if (graph.device_count >= MAX_DEVICES) {
        printf("Error: Maximum device limit reached.\n");
        return -1;
    }
    
    strcpy(graph.devices[graph.device_count].device_id, device_id);
    graph.devices[graph.device_count].adj_list = NULL;
    return graph.device_count++;
}

void add_edge(const char *from, const char *to) {
    int from_idx = add_device(from);
    int to_idx = add_device(to);
    
    if (from_idx == -1 || to_idx == -1) {
        return;
    }
    
    EdgeNode *new_edge = (EdgeNode *)malloc(sizeof(EdgeNode));
    new_edge->dest_index = to_idx;
    new_edge->next = graph.devices[from_idx].adj_list;
    graph.devices[from_idx].adj_list = new_edge;
    
    graph.adj_matrix[from_idx][to_idx] = 1;
}

void display_adjacency_matrix() {
    printf("\n=== Adjacency Matrix ===\n");
    printf("     ");
    for (int i = 0; i < graph.device_count; i++) {
        printf("%-6s ", graph.devices[i].device_id);
    }
    printf("\n");
    
    for (int i = 0; i < graph.device_count; i++) {
        printf("%-6s ", graph.devices[i].device_id);
        for (int j = 0; j < graph.device_count; j++) {
            printf("%-6d ", graph.adj_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void query_device(const char *device_id) {
    int idx = find_device_index(device_id);
    
    if (idx == -1) {
        printf("\nDevice '%s' not found in the network.\n", device_id);
        return;
    }
    
    printf("\n=== Device: %s ===\n", device_id);
    
    printf("\nOutgoing connections (sends data to):\n");
    EdgeNode *current = graph.devices[idx].adj_list;
    int has_outgoing = 0;
    while (current) {
        printf("  -> %s\n", graph.devices[current->dest_index].device_id);
        has_outgoing = 1;
        current = current->next;
    }
    if (!has_outgoing) {
        printf("  (none)\n");
    }
    
    printf("\nIncoming connections (receives data from):\n");
    int has_incoming = 0;
    for (int i = 0; i < graph.device_count; i++) {
        if (graph.adj_matrix[i][idx] == 1) {
            printf("  <- %s\n", graph.devices[i].device_id);
            has_incoming = 1;
        }
    }
    if (!has_incoming) {
        printf("  (none)\n");
    }
    printf("\n");
}

void load_communication_logs() {
    printf("Loading device communication logs...\n");
    add_edge("D001", "D002");
    add_edge("D001", "D003");
    add_edge("D002", "D004");
    add_edge("D003", "D005");
    add_edge("D004", "D005");
    add_edge("D004", "D006");
    add_edge("D005", "D007");
    add_edge("D006", "D008");
    printf("Communication network established.\n");
}

void add_connection_runtime() {
    char from[DEVICE_ID_LEN], to[DEVICE_ID_LEN];
    printf("\nEnter source device ID: ");
    scanf("%s", from);
    printf("Enter destination device ID: ");
    scanf("%s", to);
    add_edge(from, to);
    printf("Connection added: %s -> %s\n", from, to);
}

void free_graph() {
    for (int i = 0; i < graph.device_count; i++) {
        EdgeNode *current = graph.devices[i].adj_list;
        while (current) {
            EdgeNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    char device_query[DEVICE_ID_LEN];
    int choice;
    
    printf("=== Smart City Device Communication Mapper ===\n\n");
    load_communication_logs();
    
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Query device connections\n");
        printf("2. Display adjacency matrix\n");
        printf("3. Add new connection\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\nEnter device ID to query: ");
                scanf("%s", device_query);
                query_device(device_query);
                break;
            case 2:
                display_adjacency_matrix();
                break;
            case 3:
                add_connection_runtime();
                break;
            case 4:
                free_graph();
                printf("\nExiting system...\n");
                return 0;
            default:
                printf("\nInvalid choice.\n");
        }
    }
    
    return 0;
}
