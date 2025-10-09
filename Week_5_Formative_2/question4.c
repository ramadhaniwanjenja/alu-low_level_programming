#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10

typedef struct {
    int items[MAX_NODES];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

void question4() {
    printf("\n\nBFS - LEAK DETECTION\n\n");
    
    int V = 7;
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    
    // Adjacency matrix with communication durations
    int graph[7][7] = {
        {0, 6, 0, 0, 0, 0, 15},
        {6, 0, 11, 5, 0, 0, 0},
        {0, 11, 0, 17, 0, 9, 25},
        {0, 5, 17, 0, 22, 0, 0},
        {0, 0, 0, 22, 0, 10, 0},
        {0, 0, 9, 0, 10, 0, 12},
        {15, 0, 25, 0, 0, 12, 0}
    };
    
    // Input suspected employee
    char suspectChar;
    printf("Enter suspected employee node (A-G): ");
    scanf(" %c", &suspectChar);
    
    int suspect = suspectChar - 'A';
    if (suspect < 0 || suspect >= V) {
        printf("Invalid node!\n");
        return;
    }
    
    // BFS to find immediate contacts
    Queue q;
    initQueue(&q);
    int visited[MAX_NODES] = {0};
    
    visited[suspect] = 1;
    enqueue(&q, suspect);
    
    printf("\nImmediate contacts of %c:\n", vertices[suspect]);
    
    int contacts[MAX_NODES];
    int contactCount = 0;
    int maxDuration = 0;
    int mostAtRisk = -1;
    
    // Get immediate neighbors (BFS level 1)
    for (int i = 0; i < V; i++) {
        if (graph[suspect][i] != 0 && i != suspect) {
            contacts[contactCount++] = i;
            printf("%c (Duration: %d minutes)\n", vertices[i], graph[suspect][i]);
            
            if (graph[suspect][i] > maxDuration) {
                maxDuration = graph[suspect][i];
                mostAtRisk = i;
            }
        }
    }
    
    if (mostAtRisk != -1) {
        printf("\nMost at risk contact: %c (Duration: %d minutes)\n", 
               vertices[mostAtRisk], maxDuration);
    } else {
        printf("\nNo immediate contacts found.\n");
    }
}
int main() {
    question4();
    return 0;
}