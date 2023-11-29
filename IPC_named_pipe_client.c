#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"

int main() 
{
    printf("Client sending message...\n");

    // Open the FIFO for writing
    int fifo_fd = open(FIFO_PATH, O_WRONLY);
    if (fifo_fd == -1) 
    {
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    char *message = "Hello from the client!";
    ssize_t bytesWritten = write(fifo_fd, message, strlen(message));
    if (bytesWritten == -1) 
    {
        perror("Error writing to FIFO");
        exit(EXIT_FAILURE);
    }

    // Close the FIFO
    close(fifo_fd);

    return 0;
}

