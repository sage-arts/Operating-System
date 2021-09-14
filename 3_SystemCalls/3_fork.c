#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int n;
	// Take input
    	printf("Enter a non negative number, n:\n");
    	scanf("%d", &n);
    	int pid = fork();	// fork a child from parent
    	// Error Handling
    	if(pid < 0)
    	{
    		printf("Error in fork system call\nExiting program\n");
    		exit(0);
    	}
    	// Parent process
    	else if(pid > 0)
    	{
    		printf("In parent process-\n");
    		printf("Displaying sum of even numbers between 1 to %d:\n", n);
    		// calculate EVEN SUM
    		int even_sum = 0;     	
    		for(int i=2; i<=n; i+=2)
    		{
    			even_sum += i;
    		}
    		printf("%d\n", even_sum);	// print
    	}
    	// Child process
    	else
    	{
    		printf("In child process-\n");
    		printf("Displaying sum of odd numbers between 1 to %d:\n", n);
    		// calculate ODD SUM
    		int odd_sum = 0; 
    		for(int i=1; i<=n; i+=2)
    		{
    			odd_sum += i;
    		}
    		printf("%d\n", odd_sum);	// print
    	}
    	return 0;
}
