#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct {
    char *input_filename;
    char *output_filename;
    off_t write_offset;
    size_t bytes_written;
    int thread_id;
} ThreadArgs;

pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;
off_t current_offset = 0;

void* merge_file(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    FILE *input_fp;
    FILE *output_fp;
    char buffer[4096];
    size_t bytes_read;
    size_t total_bytes = 0;
    
    // Open input file for reading
    input_fp = fopen(args->input_filename, "r");
    if (input_fp == NULL) {
        printf("Thread %d: Failed to open input file %s\n", args->thread_id, args->input_filename);
        pthread_exit(NULL);
    }
    
    // Read entire input file into memory first
    fseek(input_fp, 0, SEEK_END);
    long file_size = ftell(input_fp);
    fseek(input_fp, 0, SEEK_SET);
    
    char *file_content = malloc(file_size + 1);
    if (file_content == NULL) {
        printf("Thread %d: Memory allocation failed\n", args->thread_id);
        fclose(input_fp);
        pthread_exit(NULL);
    }
    
    size_t content_size = fread(file_content, 1, file_size, input_fp);
    fclose(input_fp);
    
    // Lock mutex to get write offset and write to output file
    pthread_mutex_lock(&file_mutex);
    
    args->write_offset = current_offset;
    
    output_fp = fopen(args->output_filename, "r+");
    if (output_fp == NULL) {
        output_fp = fopen(args->output_filename, "w+");
    }
    
    if (output_fp == NULL) {
        printf("Thread %d: Failed to open output file\n", args->thread_id);
        free(file_content);
        pthread_mutex_unlock(&file_mutex);
        pthread_exit(NULL);
    }
    
    // Seek to the designated offset
    fseek(output_fp, args->write_offset, SEEK_SET);
    
    // Write the content
    total_bytes = fwrite(file_content, 1, content_size, output_fp);
    
    // Update global offset
    current_offset += total_bytes;
    
    fclose(output_fp);
    pthread_mutex_unlock(&file_mutex);
    
    args->bytes_written = total_bytes;
    free(file_content);
    
    printf("Thread %d: Merged %s (%zu bytes) at offset %ld\n", 
           args->thread_id, args->input_filename, total_bytes, args->write_offset);
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s merged_log.txt file1.txt file2.txt ... <number_of_threads>\n", argv[0]);
        return 1;
    }
    
    char *output_file = argv[1];
    int num_threads = atoi(argv[argc - 1]);
    int num_input_files = argc - 3;
    
    if (num_threads <= 0 || num_threads > num_input_files) {
        printf("Invalid number of threads. Must be between 1 and %d\n", num_input_files);
        return 1;
    }
    
    printf("Log File Merger\n");
    printf("===============\n");
    printf("Output file: %s\n", output_file);
    printf("Number of input files: %d\n", num_input_files);
    printf("Number of threads: %d\n\n", num_threads);
    
    // Remove existing output file
    remove(output_file);
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    
    pthread_t *threads = malloc(num_input_files * sizeof(pthread_t));
    ThreadArgs *thread_args = malloc(num_input_files * sizeof(ThreadArgs));
    
    if (threads == NULL || thread_args == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    int active_threads = 0;
    int file_index = 0;
    
    // Process files with limited number of concurrent threads
    while (file_index < num_input_files) {
        while (active_threads < num_threads && file_index < num_input_files) {
            thread_args[file_index].input_filename = argv[file_index + 2];
            thread_args[file_index].output_filename = output_file;
            thread_args[file_index].thread_id = file_index;
            thread_args[file_index].write_offset = 0;
            thread_args[file_index].bytes_written = 0;
            
            if (pthread_create(&threads[file_index], NULL, merge_file, &thread_args[file_index]) != 0) {
                printf("Failed to create thread for file %s\n", argv[file_index + 2]);
                file_index++;
                continue;
            }
            
            active_threads++;
            file_index++;
        }
        
        // Wait for one thread to complete
        if (active_threads > 0) {
            for (int i = 0; i < file_index; i++) {
                pthread_join(threads[i], NULL);
            }
            active_threads = 0;
        }
    }
    
    gettimeofday(&end, NULL);
    
    double elapsed = (end.tv_sec - start.tv_sec) + 
                     (end.tv_usec - start.tv_usec) / 1000000.0;
    
    size_t total_bytes = 0;
    for (int i = 0; i < num_input_files; i++) {
        total_bytes += thread_args[i].bytes_written;
    }
    
    printf("\n=== Merge Complete ===\n");
    printf("Total bytes written: %zu\n", total_bytes);
    printf("Execution time: %.6f seconds\n", elapsed);
    printf("Threads used: %d\n", num_threads);
    
    free(threads);
    free(thread_args);
    pthread_mutex_destroy(&file_mutex);
    
    return 0;
}