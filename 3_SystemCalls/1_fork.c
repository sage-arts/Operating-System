#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid1 = fork();
	int pid2 = fork();
    	int pid3 = fork();
    	// Error handling
    	if(pid1 < 0 || pid2 < 0 || pid3 < 0)
    	{
    		printf("Error in fork system call\nExiting program\n");
    		exit(0);
    	}
    	// Parent
    	if(pid1>0 && pid2>0 && pid3>0)
    	{
        	printf("Parent: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Numbering is just for hierarchy
    	// Scheduler decides the order of execution 
    	// Child1
    	else if(pid1==0 && pid2>0 && pid3>0)
    	{
        	printf("Child1: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Child2
    	else if(pid1>0 && pid2==0 && pid3>0)
    	{
        	printf("Child2: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Child3
    	else if(pid1==0 && pid2==0 && pid3>0)
    	{
        	printf("Child3: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Child4
    	else if(pid1>0 && pid2>0 && pid3==0)
    	{
		printf("Child4: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Child5
    	else if(pid1>0 && pid2==0 && pid3==0)
    	{
		printf("Child5: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Child6
    	else if(pid1==0 && pid2==0 && pid3==0)
    	{
		printf("Child6: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	// Child7
    	else if(pid1==0 && pid2>0 && pid3==0)
    	{
		printf("Child7: pid=%d ppid=%d\n", getpid(), getppid());
    	}
    	return 0;
}
