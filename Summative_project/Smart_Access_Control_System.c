#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LEN 50
#define SIMILARITY_THRESHOLD 3

typedef struct TreeNode {
    char name[MAX_NAME_LEN];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_node(const char *name) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(node->name, name);
    node->left = node->right = NULL;
    return node;
}

TreeNode *insert_bst(TreeNode *root, const char *name) {
    if (root == NULL) {
        return create_node(name);
    }
    
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = insert_bst(root->left, name);
    } else if (cmp > 0) {
        root->right = insert_bst(root->right, name);
    }
    return root;
}

int min(int a, int b, int c) {
    int min_val = a;
    if (b < min_val) min_val = b;
    if (c < min_val) min_val = c;
    return min_val;
}

int levenshtein_distance(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int matrix[len1 + 1][len2 + 1];
    
    for (int i = 0; i <= len1; i++) {
        matrix[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        matrix[0][j] = j;
    }
    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (s1[i-1] == s2[j-1]) ? 0 : 1;
            matrix[i][j] = min(
                matrix[i-1][j] + 1,
                matrix[i][j-1] + 1,
                matrix[i-1][j-1] + cost
            );
        }
    }
    
    return matrix[len1][len2];
}

TreeNode *search_exact(TreeNode *root, const char *name) {
    if (root == NULL) {
        return NULL;
    }
    
    int cmp = strcmp(name, root->name);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return search_exact(root->left, name);
    } else {
        return search_exact(root->right, name);
    }
}

void find_closest_match(TreeNode *root, const char *name, char *best_match, int *min_distance) {
    if (root == NULL) {
        return;
    }
    
    int distance = levenshtein_distance(name, root->name);
    if (distance < *min_distance) {
        *min_distance = distance;
        strcpy(best_match, root->name);
    }
    
    find_closest_match(root->left, name, best_match, min_distance);
    find_closest_match(root->right, name, best_match, min_distance);
}

void log_unrecognized(const char *name) {
    FILE *fp = fopen("unrecognized_access.log", "a");
    if (fp) {
        fprintf(fp, "%s\n", name);
        fclose(fp);
    }
}

void load_names_from_file(TreeNode **root, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Could not open file '%s'. Creating sample file...\n", filename);
        fp = fopen(filename, "w");
        fprintf(fp, "Alice\nBob\nCharlie\nDiana\nEve\nFrank\nGrace\nHenry\n");
        fclose(fp);
        fp = fopen(filename, "r");
    }
    
    char name[MAX_NAME_LEN];
    while (fgets(name, MAX_NAME_LEN, fp)) {
        name[strcspn(name, "\n")] = 0;
        if (strlen(name) > 0) {
            *root = insert_bst(*root, name);
        }
    }
    fclose(fp);
}

void verify_access(TreeNode *root, const char *name) {
    printf("\n--- Access Request ---\n");
    printf("Name entered: %s\n", name);
    
    TreeNode *exact = search_exact(root, name);
    if (exact) {
        printf("✓ ACCESS GRANTED\n");
        printf("Welcome, %s!\n", name);
        return;
    }
    
    char best_match[MAX_NAME_LEN] = "";
    int min_distance = 1000;
    find_closest_match(root, name, best_match, &min_distance);
    
    if (min_distance <= SIMILARITY_THRESHOLD) {
        printf("✗ ACCESS DENIED\n");
        printf("Did you mean: %s?\n", best_match);
        printf("(Similarity score: %d)\n", min_distance);
    } else {
        printf("✗ ACCESS DENIED\n");
        printf("Name not recognized. Logging for review.\n");
        log_unrecognized(name);
    }
}

void free_tree(TreeNode *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    TreeNode *root = NULL;
    char input_name[MAX_NAME_LEN];
    
    printf("=== Smart Access Control System ===\n");
    printf("Loading authorized personnel...\n");
    
    load_names_from_file(&root, "authorized_names.txt");
    printf("Authorized names loaded successfully.\n\n");
    
    while (1) {
        printf("\nEnter name (or 'quit' to exit): ");
        fgets(input_name, MAX_NAME_LEN, stdin);
        input_name[strcspn(input_name, "\n")] = 0;
        
        if (strcmp(input_name, "quit") == 0) {
            break;
        }
        
        if (strlen(input_name) > 0) {
            verify_access(root, input_name);
        }
    }
    
    free_tree(root);
    printf("\nSystem shutdown.\n");
    return 0;
}
