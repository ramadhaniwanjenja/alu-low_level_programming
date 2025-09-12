#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // For Sleep

typedef struct Node {
    char stop[50];
    struct Node *prev;
    struct Node *next;
} Node;

Node *createNode(char *stop) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->stop, stop);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addEnd(Node **head, char *stop) {
    Node *newNode = createNode(stop);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

void traverseForward(Node *head) {
    Node *temp = head;
    while (temp) {
        printf("Next stop: %s\n", temp->stop);
        fflush(stdout); // Ensure immediate print
        Sleep(3000);    // 3-second delay (milliseconds)
        temp = temp->next;
    }
}

void traverseBackward(Node *head) {
    Node *temp = head;
    while (temp->next) temp = temp->next; // Move to last node
    while (temp) {
        printf("Next stop: %s\n", temp->stop);
        fflush(stdout);
        Sleep(3000);
        temp = temp->prev;
    }
}

int main() {
    Node *head = NULL;
    char stops[][50] = {"Home", "Stop1", "Stop2", "Campus"};
    for (int i = 0; i < 4; i++) addEnd(&head, stops[i]);

    int choice;
    printf("1: Forward, 2: Backward\n");
    scanf("%d", &choice);
    if (choice == 1) traverseForward(head);
    else if (choice == 2) traverseBackward(head);
    else printf("Invalid choice!\n");

    // Free memory (simplified, actual cleanup needed)
    return 0;
}