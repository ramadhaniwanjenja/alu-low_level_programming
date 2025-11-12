#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_RANGE 100000
#define NUM_THREADS 20

typedef struct {
    int start;
    int end;
    int local_count;
} ThreadData;

int global_palindrome_count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

int is_palindrome(int num) {
    int original = num;
    int reversed = 0;
    int remainder;
    
    while (num != 0) {
        remainder = num % 10;
        reversed = reversed * 10 + remainder;
        num /= 10;
    }
    
    return (original == reversed);
}

void* count_palindromes(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int local_count = 0;
    
    for (int i = data->start; i <= data->end; i++) {
        if (is_palindrome(i)) {
            local_count++;
        }
    }
    
    data->local_count = local_count;
    
    pthread_mutex_lock(&count_mutex);
    global_palindrome_count += local_count;
    pthread_mutex_unlock(&count_mutex);
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    int range_per_thread = (MAX_RANGE + 1) / NUM_THREADS;
    
    printf("Starting palindrome count with %d threads...\n", NUM_THREADS);
    printf("Range: 0 to %d\n\n", MAX_RANGE);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * range_per_thread;
        thread_data[i].end = (i == NUM_THREADS - 1) ? MAX_RANGE : (i + 1) * range_per_thread - 1;
        thread_data[i].local_count = 0;
        
        if (pthread_create(&threads[i], NULL, count_palindromes, &thread_data[i]) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }
    
    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(1);
        }
        printf("Thread %2d (range %6d-%6d): found %d palindromes\n", 
               i, thread_data[i].start, thread_data[i].end, thread_data[i].local_count);
    }
    
    printf("\nThe Synchronize total number of palindromic number from 0 to %d is %d\n", 
           MAX_RANGE, global_palindrome_count);
    
    pthread_mutex_destroy(&count_mutex);
    
    return 0;
}