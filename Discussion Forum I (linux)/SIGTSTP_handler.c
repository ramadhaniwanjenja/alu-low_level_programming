#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Flag to control the main loop
volatile sig_atomic_t keep_running = 1;

// Signal handler function for SIGTSTP
void handle_sigtstp(int sig) {
    printf("\nReceived SIGTSTP (Ctrl+Z). Shutting down gracefully...\n");
    keep_running = 0;  // Set flag to stop the loop
}

int main() {
    // Register the signal handler for SIGTSTP
    struct sigaction sa;
    sa.sa_handler = handle_sigtstp;  // Set our custom handler
    sigemptyset(&sa.sa_mask);        // No additional signals blocked
    sa.sa_flags = 0;                 // No special flags
    
    if (sigaction(SIGTSTP, &sa, NULL) == -1) {
        perror("Error setting up signal handler");
        return 1;
    }
    
    printf("Program is running... Press Ctrl+Z to terminate gracefully.\n");
    
    // Main loop - keeps running until signal is received
    int counter = 0;
    while (keep_running) {
        printf("Still running... (count: %d)\n", counter++);
        sleep(2);  // Wait 2 seconds between messages
    }
    
    // Cleanup code runs after signal is received
    printf("Program terminated cleanly. Goodbye!\n");
    return 0;
}

