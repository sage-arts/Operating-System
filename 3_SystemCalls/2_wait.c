#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int status;
     	// Child process
     	if(fork() == 0)
     	{
     		printf("Hello, this is child\n");
     		exit(1);	// EXIT_FAILURE, just to check exit status
     	} 
     	// Parent process  
     	else
     	{  
     		// here parent has single child  
     		// parent process goes to wait state until child terminates 
         	wait(&status);		// define exit status
         	printf("Parent: I was waiting for child\n");
     	}    
     	if(WIFEXITED(status))	// if child exited
     	{
     		// print exit status
          	printf("Child terminated with status: %d\n", WEXITSTATUS(status));
     	}    
     	return 0;
}
