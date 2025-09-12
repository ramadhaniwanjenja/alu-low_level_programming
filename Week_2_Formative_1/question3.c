#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data) root->left = insertNode(root->left, data);
    else root->right = insertNode(root->right, data);
    return root;
}

Node *getRoot(Node *root) {
    return root;
}

void printLeafNodes(Node *root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
        return;
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

void printSiblings(Node *root, int target) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return;
    if (root->left && root->right) {
        if (root->left->data == target) printf("%d ", root->right->data);
        if (root->right->data == target) printf("%d ", root->left->data);
    }
    printSiblings(root->left, target);
    printSiblings(root->right, target);
}

Node *findParent(Node *root, int target) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return NULL;
    if ((root->left && root->left->data == target) || (root->right && root->right->data == target))
        return root;
    Node *parent = findParent(root->left, target);
    if (parent == NULL) parent = findParent(root->right, target);
    return parent;
}

void printGrandchildren(Node *root, int target) {
    Node *parent = findParent(root, target);
    if (parent) {
        if (parent->left && parent->left->data == target) {
            if (parent->right) printLeafNodes(parent->right);
        } else if (parent->right && parent->right->data == target) {
            if (parent->left) printLeafNodes(parent->left);
        }
    }
}

int main() {
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    Node *root = NULL;
    for (int i = 0; i < 7; i++) root = insertNode(root, arr[i]);

    printf("Root: %d\n", getRoot(root)->data);
    printf("Leaf Nodes: "); printLeafNodes(root); printf("\n");
    printf("Siblings of 40: "); printSiblings(root, 40); printf("\n");
    Node *parent = findParent(root, 40);
    printf("Parent of 40: %d\n", parent ? parent->data : -1);
    printf("Grandchildren of 30: "); printGrandchildren(root, 30); printf("\n");

    // Time complexity for adding a node: O(h) where h is height, O(n) in worst case
    return 0;
}