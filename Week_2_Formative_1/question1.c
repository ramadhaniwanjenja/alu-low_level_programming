#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    int grade;
} Student;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Student arr[], int low, int high) {
    int pivot = arr[high].grade;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].grade <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    FILE *inputFile = fopen("students.txt", "r");
    FILE *outputFile = fopen("sorted_students.txt", "w");
    if (!inputFile || !outputFile) {
        printf("Error opening files!\n");
        return 1;
    }

    Student students[100];
    int count = 0;
    while (count < 100 && fscanf(inputFile, "%s %s %d", students[count].firstName, students[count].lastName, &students[count].grade) == 3) {
        count++;
    }
    fclose(inputFile);

    quickSort(students, 0, count - 1);

    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "%s %s %d\n", students[i].firstName, students[i].lastName, students[i].grade);
    }
    fclose(outputFile);

    printf("Sorting complete. Check sorted_students.txt\n");
    return 0;
}