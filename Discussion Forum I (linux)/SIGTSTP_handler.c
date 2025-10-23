#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Flag to control main loop
volatile sig_atomic_t keep_running = 1;

// Handler for SIGTSTP signal
void handle_sigtstp(int sig) {
    printf("\nCtrl+Z pressed. Exiting gracefully...\n");
    keep_running = 0;
}

int main() {
    // Setup signal handler with sigaction
    struct sigaction sa;
    sa.sa_handler = handle_sigtstp;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTSTP, &sa, NULL);
    
    printf("Running... Press Ctrl+Z to stop.\n");
    
    // Main loop
    int count = 0;
    while (keep_running) {
        printf("Working... (%d)\n", count++);
        sleep(2);
    }
    
    printf("Done!\n");
    return 0;
}

