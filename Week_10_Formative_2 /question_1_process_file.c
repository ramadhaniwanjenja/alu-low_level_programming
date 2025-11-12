#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
    pid_t pid;
    int status;
    char *args[] = {"ls", "-l", NULL};
    
    printf("Parent Process (PID: %d) starting...\n", getpid());
    
    // Create a child process
    pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process
        printf("Child Process (PID: %d) executing command...\n", getpid());
        execvp(args[0], args);
        
        // If execvp returns, it must have failed
        perror("execvp failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent Process waiting for child (PID: %d)...\n", pid);
        
        // Create a temporary file
        char temp_filename[] = "/tmp/tempfile_XXXXXX";
        int fd = mkstemp(temp_filename);
        
        if (fd == -1) {
            perror("Failed to create temporary file");
            exit(1);
        }
        
        printf("Parent Process created temporary file: %s\n", temp_filename);
        
        // Write to the temporary file
        const char *message = "This is a test message written by the parent process.\n";
        ssize_t bytes_written = write(fd, message, strlen(message));
        
        if (bytes_written == -1) {
            perror("Write failed");
            close(fd);
            unlink(temp_filename);
            exit(1);
        }
        
        printf("Parent Process wrote %zd bytes to the file.\n", bytes_written);
        
        // Move file pointer back to the beginning
        lseek(fd, 0, SEEK_SET);
        
        // Read from the temporary file
        char buffer[256];
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        
        if (bytes_read == -1) {
            perror("Read failed");
            close(fd);
            unlink(temp_filename);
            exit(1);
        }
        
        buffer[bytes_read] = '\0';
        printf("Parent Process read from file: %s", buffer);
        
        // Close and delete the temporary file
        close(fd);
        unlink(temp_filename);
        printf("Parent Process cleaned up temporary file.\n");
        
        // Wait for child process to complete
        wait(&status);
        
        if (WIFEXITED(status)) {
            printf("Child Process exited with status %d\n", WEXITSTATUS(status));
        }
    }
    
    return 0;
}