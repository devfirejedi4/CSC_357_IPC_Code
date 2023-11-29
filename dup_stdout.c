#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    // Save the current standard output
    int saved_stdout = dup(1);

    printf("Writing to standard out\n");

    // Open a file for writing
    int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_fd == -1) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Redirect standard output to the file
    if (dup2(file_fd, 1) == -1) 
    {
        perror("Error redirecting standard output");
        exit(EXIT_FAILURE);
    }

    // Write to standard output (now redirected) and print
    printf("Writing to stdout (after redirection)");
    fflush(stdout);

    // Step 6: Restore the original standard output
    if (dup2(saved_stdout, 1) == -1) 
    {
        perror("Error restoring standard output");
        exit(EXIT_FAILURE);
    }

    // Write to standard output (restored) and print
    printf("Writing to original standard output\n");

    // Close the file descriptor for the opened file
    close(file_fd);

    return 0;
}
