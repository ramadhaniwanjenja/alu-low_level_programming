#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char lastName[50];
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(char *lastName) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->lastName, lastName);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *root, char *lastName) {
    if (root == NULL) return createNode(lastName);
    if (strcmp(lastName, root->lastName) < 0) root->left = insertNode(root->left, lastName);
    else root->right = insertNode(root->right, lastName);
    return root;
}

Node *searchNode(Node *root, char *lastName) {
    if (root == NULL || strcmp(root->lastName, lastName) == 0) return root;
    if (strcmp(lastName, root->lastName) < 0) return searchNode(root->left, lastName);
    return searchNode(root->right, lastName);
}

int main() {
    FILE *inputFile = fopen("students.txt", "r");
    if (!inputFile) {
        printf("Error opening file!\n");
        return 1;
    }

    Node *root = NULL;
    char firstName[50], lastName[50], grade[10];
    while (fscanf(inputFile, "%s %s %s", firstName, lastName, grade) == 3) {
        root = insertNode(root, lastName);
    }
    fclose(inputFile);

    char searchName[50];
    printf("Enter last name to search: ");
    scanf("%s", searchName);
    Node *result = searchNode(root, searchName);
    if (result) printf("Student with last name %s found!✅\n", searchName);
    else printf("Student with last name %s not found!❌\n", searchName);

    // Free memory (simplified)
    return 0;
}