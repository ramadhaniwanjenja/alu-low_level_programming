#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 4
#define MAX_ENTRIES 100
#define MAX_LENGTH 500

void encrypt_entry(char *text);
void decrypt_entry(char *text);

char entries[MAX_ENTRIES][MAX_LENGTH];
int entry_count = 0;

void add_entry() {
    if (entry_count >= MAX_ENTRIES) {
        printf("Diary is full!\n");
        return;
    }
    
    printf("Enter your diary entry:\n");
    getchar();
    fgets(entries[entry_count], MAX_LENGTH, stdin);
    
    encrypt_entry(entries[entry_count]);
    entry_count++;
    printf("Entry added and encrypted successfully!\n");
}

void view_entries() {
    char password[20];
    printf("Enter password to view entries: ");
    scanf("%s", password);
    
    if (strcmp(password, "1234") != 0) {
        printf("Incorrect password!\n");
        return;
    }
    
    if (entry_count == 0) {
        printf("No entries found.\n");
        return;
    }
    
    printf("\n===== Diary Entries =====\n");
    int i;
    for (i = 0; i < entry_count; i++) {
        char temp[MAX_LENGTH];
        strcpy(temp, entries[i]);
        decrypt_entry(temp);
        printf("Entry %d: %s", i + 1, temp);
    }
    printf("=========================\n");
}

void encrypt_entry(char *text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        text[i] = text[i] + KEY;
    }
}

void decrypt_entry(char *text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        text[i] = text[i] - KEY;
    }
}

int main() {
    int choice;
    
    while (1) {
        printf("\n===== Diary Manager =====\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            add_entry();
        } else if (choice == 2) {
            view_entries();
        } else if (choice == 3) {
            printf("Goodbye!\n");
            break;
        } else {
            printf("Invalid choice!\n");
        }
    }
    
    return 0;
}

