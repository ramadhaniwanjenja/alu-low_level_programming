#include <stdio.h>
#include <string.h>

#define KEY 4

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

