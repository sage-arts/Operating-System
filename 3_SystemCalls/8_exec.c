#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Displaying contents of the Home directory:\n");
	// (char*) for typecasting
	// name of executable file/command (Path environment variable)
    	char *programName = (char*)"ls";
    	// arguments we want to pass to the command (ls)
    	char *arg1 = (char*)"-lh";
    	char *arg2 = (char*)"/home";
    	execlp(programName, programName, arg1, arg2, NULL);
    	return 0;
}
