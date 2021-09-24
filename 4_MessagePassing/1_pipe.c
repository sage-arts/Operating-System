#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define buffsize 100

int main()
{
	char p1wmsg[buffsize], p1rmsg[buffsize];
	int p2wmsg, p2rmsg;
	printf("Enter a string: ");
	scanf("%s", p1wmsg);
	// two pipes 1 and 2
	// two descriptors for each pipe [0] to read, [1] to write
	int pipe1des[2], pipe2des[2];
	// create pipe1 for one-way communication i.e. parent writes, child
	// reads
	if(pipe(pipe1des) == -1) 
	{
		printf("Error in creating pipe1\n");
	}
	// create pipe2 for other-way communication i.e. child writes, parent 
	// reads
	if(pipe(pipe2des) == -1) 
	{
		printf("Error in creating pipe2\n");
	}
	// parent process
	if(fork() > 0)
	{
		close(pipe1des[0]);	// close pipe1 unwanted read side
		close(pipe2des[1]);	// close pipe2 unwanted write side
		// write string to pipe1
		write(pipe1des[1], p1wmsg, sizeof(p1wmsg));
		// read ASCII Sum from pipe2
		read(pipe2des[0], &p2rmsg, sizeof(p2rmsg));
		printf("Parent- ASCII Sum from child: %d\n", p2rmsg);
	}
	// child process
	else 
	{
		close(pipe1des[1]);	// close pipe1 unwanted write side
		close(pipe2des[0]);	// close pipe2 unwanted read side
		// read string from pipe1
		read(pipe1des[0], p1rmsg, sizeof(p1rmsg));
		// calculate ASCII Sum by adding ASCII values of characters of 
		// the string, typecast to int gives ASCII value of a character 
		p2wmsg = 0;
		for(int i=0; i<strlen(p1rmsg); i++)
		{
			p2wmsg += (int)p1rmsg[i];
		}
		// write ASCII Sum to pipe2
		write(pipe2des[1], &p2wmsg, sizeof(p2wmsg));
	}
	return 0;
}
