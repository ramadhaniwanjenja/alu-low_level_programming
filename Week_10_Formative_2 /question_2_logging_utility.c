#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define NUM_ENTRIES 1000000

// Unbuffered I/O version
void unbuffered_logging() {
    int fd;
    char log_entry[128];
    struct timeval tv;
    
    fd = open("unbuffered_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open unbuffered log file");
        exit(1);
    }
    
    for (int i = 0; i < NUM_ENTRIES; i++) {
        gettimeofday(&tv, NULL);
        snprintf(log_entry, sizeof(log_entry), "[%ld.%06ld] Log entry number %d\n", 
                 tv.tv_sec, tv.tv_usec, i);
        write(fd, log_entry, strlen(log_entry));
    }
    
    close(fd);
}

// Buffered I/O version
void buffered_logging() {
    FILE *fp;
    char log_entry[128];
    struct timeval tv;
    
    fp = fopen("buffered_log.txt", "w");
    if (fp == NULL) {
        perror("Failed to open buffered log file");
        exit(1);
    }
    
    for (int i = 0; i < NUM_ENTRIES; i++) {
        gettimeofday(&tv, NULL);
        snprintf(log_entry, sizeof(log_entry), "[%ld.%06ld] Log entry number %d\n", 
                 tv.tv_sec, tv.tv_usec, i);
        fprintf(fp, "%s", log_entry);
    }
    
    fclose(fp);
}

int main(int argc, char *argv[]) {
    struct timeval start, end;
    double elapsed;
    
    if (argc != 2) {
        printf("Usage: %s <buffered|unbuffered>\n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "unbuffered") == 0) {
        printf("Running unbuffered I/O logging...\n");
        gettimeofday(&start, NULL);
        unbuffered_logging();
        gettimeofday(&end, NULL);
        
        elapsed = (end.tv_sec - start.tv_sec) + 
                  (end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Unbuffered I/O completed in %.6f seconds\n", elapsed);
        printf("Output file: unbuffered_log.txt\n");
        
    } else if (strcmp(argv[1], "buffered") == 0) {
        printf("Running buffered I/O logging...\n");
        gettimeofday(&start, NULL);
        buffered_logging();
        gettimeofday(&end, NULL);
        
        elapsed = (end.tv_sec - start.tv_sec) + 
                  (end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Buffered I/O completed in %.6f seconds\n", elapsed);
        printf("Output file: buffered_log.txt\n");
        
    } else {
        printf("Invalid argument. Use 'buffered' or 'unbuffered'\n");
        return 1;
    }
    
    return 0;
}