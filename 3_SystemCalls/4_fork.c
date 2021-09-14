#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int a[10];
	// Take input
	printf("Enter ten numbers\n");
	for(int i=0; i<10; i++)
	{
		printf("Enter number%d: ", i+1);
		scanf("%d", &a[i]);
	}
	pid_t cpid;
    	int pid = fork();	// fork a child from parent
    	int i, j, x;
    	// Error handling 
    	if(pid < 0)
    	{
    		printf("Error in fork system call\nExiting program\n");
    		exit(0);
    	}
    	// Child process
    	else if(pid == 0)
    	{
    		printf("In child process-\n");
    		printf("Displaying numbers in descending order:\n");
    		// Do reverse sort
		for(i=1; i<10; i++)
		{
			x = a[i];
			j = i-1;
			while(j >= 0 && a[j] < x)
			{
				a[j+1] = a[j];
				j--; 
			}
			a[j+1] = x;
		}
		// print output
		for(i=0; i<10; i++)
		{
			printf("%d ", a[i]);
		}
		printf("\n");
		exit(0);	// EXIT_SUCCESS
    	}
    	// Parent process;
    	else
    	{
    		cpid = wait(NULL);	// use null as we dont care about exit status
    		// parent process goes to wait state until child terminates
    		printf("In parent process-\n");
    		printf("Displaying numbers in ascending order:\n");
    		// Do sorting
		for(i=1; i<10; i++)
		{
			x = a[i];
			j = i-1;
			while(j >= 0 && a[j] > x)
			{
				a[j+1] = a[j];
				j--; 
			}
			a[j+1] = x;
		}
		// print output
		for(i=0; i<10; i++)
		{
			printf("%d ", a[i]);
		}
		printf("\n");
    	}
    	return 0;
}
