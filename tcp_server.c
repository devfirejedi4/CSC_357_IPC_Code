#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() 
{
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to the server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) 
    {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) == -1) 
    {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("TCP Server listening on port %d...\n", PORT);

    // Accept incoming connections
    if ((newsockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len)) == -1) 
    {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    // Receive data from client
    memset(buffer, 0, sizeof(buffer));
    recv(newsockfd, buffer, BUFFER_SIZE, 0);
    printf("Received from client: %s\n", buffer);

    close(newsockfd);
    close(sockfd);
    return 0;
}
