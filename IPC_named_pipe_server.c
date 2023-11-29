#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"

int main() {
    // Create the FIFO (named pipe) if it doesn't exist
    if (mkfifo(FIFO_PATH, 0666) == -1) 
    {
        perror("Error creating FIFO");
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for messages...\n");

    int fifo_fd = open(FIFO_PATH, O_RDONLY);
    if (fifo_fd == -1) 
    {
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }

    // Read from the FIFO
    char buffer[100];
    ssize_t bytesRead = read(fifo_fd, buffer, sizeof(buffer));
    if (bytesRead == -1) 
    {
        perror("Error reading from FIFO");
        exit(EXIT_FAILURE);
    }

    // Null-terminate the received data
    buffer[bytesRead] = '\0';

    // Print the received message
    printf("Server received message: %s\n", buffer);

    // Close and remove the FIFO
    close(fifo_fd);
    unlink(FIFO_PATH);

    return 0;
}

