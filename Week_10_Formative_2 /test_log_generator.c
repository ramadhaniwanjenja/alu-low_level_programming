#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generate_log_file(const char *filename, int num_entries) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to create log file");
        exit(1);
    }
    
    time_t now = time(NULL);
    
    for (int i = 0; i < num_entries; i++) {
        fprintf(fp, "[%ld] Log entry %d from %s - Sample log message for testing\n", 
                now + i, i, filename);
    }
    
    fclose(fp);
    printf("Generated %s with %d entries\n", filename, num_entries);
}

int main() {
    printf("Generating test log files...\n\n");
    
    generate_log_file("file1.txt", 1000);
    generate_log_file("file2.txt", 1500);
    generate_log_file("file3.txt", 2000);
    generate_log_file("file4.txt", 1200);
    generate_log_file("file5.txt", 800);
    
    printf("\nTest files created successfully!\n");
    printf("You can now run: ./q4_merger merged_log.txt file1.txt file2.txt file3.txt file4.txt file5.txt 2\n");
    
    return 0;
}