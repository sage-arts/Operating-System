#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	pid_t cpid;
	int pid = fork();	// fork a child from parent
	// Error handling
	if(pid < 0)
    	{
    		printf("Error in fork system call\nExiting program\n");
    		exit(0);
    	}
    	// Child process
     	else if(pid == 0)
     	{
     		char dir[100];
     		// Take input
		printf("Enter path of the directory to display its contents:\n");
		scanf("%s", dir);
		// (char*) for typecasting
		// name of executable file/command (Path environment variable)
     		char *programName = (char*)"ls";	
     		char *args[4];
     		args[0] = programName;
     		// arguments we want to pass to the command (ls)
     		args[1] = (char*)"-lh";	
     		args[2] = (char*)dir;	// path of directory entered by user
     		args[3] = NULL;
     		execvp(programName, args);
     		exit(0);
     	}
     	// Parent process
     	else
     	{
     		cpid = wait(NULL);
     		printf("\nDisplaying the process tree:\n");
     		char *args[2];
     		args[0] = (char*)"/bin/pstree";	// path of executable file
     		args[1] = NULL;
     		execv(args[0], args);
     	}
     	return 0;
}
