#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char buffer[100];

    // Save the current standard input
    int saved_stdin = dup(0);
   
    // Read from standard input and print
    printf("Reading from stdin (connected to terminal):\n");
    fgets(buffer, sizeof(buffer), stdin);
    printf("stdin read: %s\n", buffer);

    // Open a file for reading
    int file_fd = open("input.txt", O_RDONLY);
    if (file_fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Redirect standard input to the file
    if (dup2(file_fd, 0) == -1)
    {
        perror("Error redirecting standard input");
        exit(EXIT_FAILURE);
    }
    printf("stdin successfully redirected to input.txt!\n");

    // Read from standard input (now redirected) and print
    printf("Reading from stdin (after redirection):\n");
    fgets(buffer, sizeof(buffer), stdin);
    printf("stdin read: %s\n", buffer);

    // Restore the original standard input
    if (dup2(saved_stdin, 0) == -1)
    {
        perror("Error restoring standard input");
        exit(EXIT_FAILURE);
    }

    // Read from standard input (restored) and print
    printf("Reading from original standard input:\n");
    fgets(buffer, sizeof(buffer), stdin);
    printf("stdin read: %s", buffer);

    // Close the file descriptor for the opened file
    close(file_fd);

    return 0;
}
