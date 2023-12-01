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
	printf("(child) pid = %d\n", getpid());
	
        close(pipe_fd[1]);  // Close the write end of the pipe

        // Read from the pipe
        char buffer[100];
        if(read(pipe_fd[0], buffer, sizeof(buffer)) == -1)
        {
            perror("Read failed");
            exit(EXIT_FAILURE);
        }
        printf("Child received: %s\n", buffer);

        // Close the read end of the pipe in the child
        close(pipe_fd[0]);
    } 
    else 
    {
    	// Parent process
    	printf("(parent) pid = %d\n", getpid());
    
        close(pipe_fd[0]);  // Close the read end of the pipe

        // Write to the pipe
        char *message = "Hello from the parent!";
        
        // Sleep for 3 seconds before writing to the pipe
        sleep(3);

	if(write(pipe_fd[1], message, strlen(message) + 1) == -1)
        {
            perror("Write failed");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe in the parent
        close(pipe_fd[1]);

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}
