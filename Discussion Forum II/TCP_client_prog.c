#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    
    // Create socket - this makes the connection possible
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Could not create socket\n");
        return 1;
    }
    printf("Socket created succesfully\n");
    
    // Setup server address structure
    server.sin_addr.s_addr = inet_addr("127.0.0.1");  // localhost for testing
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);  // port 8888
    
    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("connect failed. Error\n");
        return 1;
    }
    
    printf("Connected to server!\n");
    
    // Send some data to the server
    printf("Enter message to send: ");
    fgets(message, 1000, stdin);
    
    if(send(sock, message, strlen(message), 0) < 0) {
        printf("Send failed\n");
        return 1;
    }
    printf("Data sent to server\n");
    
    // Recieve a reply from server
    if(recv(sock, server_reply, 2000, 0) < 0) {
        printf("recv failed\n");
    }
    printf("Server reply: %s\n", server_reply);
    
    close(sock);
    return 0;
}

