#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    FILE *file;
    pid_t child_pid;

    // Open a file for writing
    file = fopen("communication_file.txt", "w");
    if (file == NULL) 
    {
        perror("Error opening file");
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
    	
        fclose(file);  // Close the file in the child

        // Open the file for reading
        file = fopen("communication_file.txt", "r");
        if (file == NULL) 
	{
            perror("Error opening file in child");
            exit(EXIT_FAILURE);
        }

        // Read and print the message
        char buffer[100];
        fgets(buffer, sizeof(buffer), file);
        printf("Child received: %s", buffer);

        fclose(file);  // Close the file in the child
    } 
    else 
    {
    	// Parent process
    	printf("(parent) pid = %d\n", getpid());
    
    	// sleep(3);
        fprintf(file, "Hello from the parent!\n");
        fclose(file);  // Close the file in the parent

        // Wait for the child to finish
        wait(NULL);
    }

    return 0;
}

