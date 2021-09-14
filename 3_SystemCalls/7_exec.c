#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Displaying contents of the current directory:\n");
	char *args[2];
     	args[0] = (char*)"/bin/ls";	// path of executable file
     	args[1] = NULL;			// terminated by NULL
     	execv(args[0], args); 
     	return 0;
}
