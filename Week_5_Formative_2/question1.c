#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent a task with name and priority
typedef struct {
    char name;
    int priority;
} Task;

// Function to swap two tasks
void swap(Task* a, Task* b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain max-heap property
void heapify(Task heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && heap[left].priority > heap[largest].priority)
        largest = left;
    
    if (right < n && heap[right].priority > heap[largest].priority)
        largest = right;
    
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(heap, n, largest);
    }
}

// Build max heap from array
void buildMaxHeap(Task heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

// Insert element into max heap
int insertHeap(Task heap[], int n, Task newTask) {
    heap[n] = newTask;
    int i = n;
    
    while (i > 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return n + 1;
}

// Delete root from max heap
int deleteRoot(Task heap[], int n) {
    if (n <= 0) return 0;
    
    heap[0] = heap[n - 1];
    n--;
    heapify(heap, n, 0);
    return n;
}

// Print heap
void printHeap(Task heap[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c(%d) ", heap[i].name, heap[i].priority);
    }
    printf("\n");
}

void question1() {
    printf("\n========== QUESTION 1: TASK PRIORITY SCHEDULING ==========\n\n");
    
    int priorities[] = {21, 18, 85, 15, 36, 75, 63, 65, 90, 70, 89};
    char names[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
    int n = 11;
    
    Task heap[MAX_SIZE];
    
    // Create initial array with names
    for (int i = 0; i < n; i++) {
        heap[i].name = names[i];
        heap[i].priority = priorities[i];
    }
    
    printf("Original Array:\n");
    printHeap(heap, n);
    
    // Build max heap
    buildMaxHeap(heap, n);
    printf("\nMax Heap after construction:\n");
    printHeap(heap, n);
    
    // Insert task with priority 96
    Task newTask = {'L', 96};
    n = insertHeap(heap, n, newTask);
    printf("\nAfter inserting task L(96):\n");
    printHeap(heap, n);
    
    // Delete task with priority 96 (root)
    n = deleteRoot(heap, n);
    printf("\nAfter deleting task L(96):\n");
    printHeap(heap, n);
}
int main() {
    question1();
    return 0;
}
