#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() 
{
    int pipe_fd[2];
    pid_t child_pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1)
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    child_pid = fork();

    if (child_pid == -1) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) 
    {
    	// Child process
	printf("(child) pid = %d\n", child_pid);
	
        close(pipe_fd[1]);  // Close the write end of the pipe

        // Read from the pipe
        char buffer[100];
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        // optional: close(pipe_fd[0]);  // Close the read end of the pipe in the child
    } 
    else 
    {
    	// Parent process
    	printf("(parent) pid = %d\n", getpid());
    
        close(pipe_fd[0]);  // Close the read end of the pipe

        // Write to the pipe
        char *message = "Hello from the parent!";
        // sleep(3);
	write(pipe_fd[1], message, strlen(message) + 1);

        // optional: close(pipe_fd[1]);  // Close the write end of the pipe in the parent

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}

