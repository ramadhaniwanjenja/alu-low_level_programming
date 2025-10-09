#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct {
    char name[20];
    int severity;
} Patient;

void swapPatient(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyPatient(Patient heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && heap[left].severity > heap[largest].severity)
        largest = left;
    
    if (right < n && heap[right].severity > heap[largest].severity)
        largest = right;
    
    if (largest != i) {
        swapPatient(&heap[i], &heap[largest]);
        heapifyPatient(heap, n, largest);
    }
}

void buildPatientHeap(Patient heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyPatient(heap, n, i);
    }
}

int insertPatient(Patient heap[], int n, Patient newPatient) {
    heap[n] = newPatient;
    int i = n;
    
    while (i > 0 && heap[(i - 1) / 2].severity < heap[i].severity) {
        swapPatient(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return n + 1;
}

Patient extractMax(Patient heap[], int* n) {
    Patient max = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    heapifyPatient(heap, *n, 0);
    return max;
}

void printPatientHeap(Patient heap[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s(%d) ", heap[i].name, heap[i].severity);
    }
    printf("\n");
}

void question2() {
    printf("\n\n========== QUESTION 2: EMERGENCY ROOM TRIAGE ==========\n\n");
    
    Patient patients[MAX_SIZE] = {
        {"John", 70},
        {"Maria", 85},
        {"Liam", 60},
        {"Amina", 92},
        {"Grace", 78},
        {"David", 55}
    };
    int n = 6;
    
    printf("Original Patient List:\n");
    printPatientHeap(patients, n);
    
    // Build max heap
    buildPatientHeap(patients, n);
    printf("\nMax Heap (Priority Queue):\n");
    printPatientHeap(patients, n);
    
    // Extract priority queue (treatment order)
    printf("\nTreatment Order (Priority Queue):\n");
    Patient tempHeap[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        tempHeap[i] = patients[i];
    }
    int tempN = n;
    int order = 1;
    while (tempN > 0) {
        Patient p = extractMax(tempHeap, &tempN);
        printf("%d. %s (Severity: %d)\n", order++, p.name, p.severity);
    }
    
    // Insert new patient with severity 96
    Patient newPatient = {"Emma", 96};
    n = insertPatient(patients, n, newPatient);
    printf("\nAfter inserting Emma(96):\n");
    printPatientHeap(patients, n);
    
    // Remove Emma (root)
    n--;
    patients[0] = patients[n];
    heapifyPatient(patients, n, 0);
    printf("\nAfter removing Emma(96):\n");
    printPatientHeap(patients, n);
}
int main() {
    question2();
    return 0;
}