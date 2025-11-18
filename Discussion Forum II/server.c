#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;
    char client_message[2000];
    
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket\n");
    }
    printf("Socket created\n");
    
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    
    // Bind - this attaches socket to port 8888
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("bind failed\n");
        return 1;
    }
    printf("bind done\n");
    
    // Listen for incoming connections
    listen(socket_desc, 3);
    
    printf("Waiting for incoming connections on port 8888...\n");
    c = sizeof(struct sockaddr_in);
    
    // Accept connection from client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0) {
        printf("accept failed\n");
        return 1;
    }
    printf("Connection accepted\n");
    
    // Receive message from client
    int read_size;
    while((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        printf("Client says: %s\n", client_message);
        
        // Send reply to client
        char *reply = "Message received by server!";
        write(client_sock, reply, strlen(reply));
        
        memset(client_message, 0, 2000); // clear buffer
    }
    
    if(read_size == 0) {
        printf("Client disconnected\n");
    }
    
    return 0;
}