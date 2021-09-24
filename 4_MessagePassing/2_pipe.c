#include <stdio.h>
#include <unistd.h>

int main()
{
	int n;
	printf("Enter the number of elements in the array: ");
	scanf("%d", &n);
	int p1wmsg[n], p1rmsg[n], p2wmsg[n], p2rmsg[n];
	printf("Enter the elements of the array:\n");
	for(int i=0; i<n; i++)
	{
		scanf("%d", &p1wmsg[i]);
	}
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
		// sort array in ascending order
		int i, j, x;
		for(i=1; i<n; i++)
		{
			x = p1wmsg[i];
			j = i-1;
			while(j >= 0 && p1wmsg[j] > x)
			{
				p1wmsg[j+1] = p1wmsg[j];
				j--; 
			}
			p1wmsg[j+1] = x;
		}
		// write array in ascending order to pipe1
		write(pipe1des[1], p1wmsg, sizeof(p1wmsg));
		// read array in descending order from pipe2
		read(pipe2des[0], p2rmsg, sizeof(p2rmsg));
		printf("Parent- Array in descendng order from child:\n");
		for(int i=0; i<n; i++)
		{
			printf("%d\n", p2rmsg[i]);
		}
	}
	// child process
	else 
	{
		close(pipe1des[1]);	// close pipe1 unwanted write side
		close(pipe2des[0]);	// close pipe2 unwanted read side
		// read array in ascending order from pipe1
		read(pipe1des[0], p1rmsg, sizeof(p1rmsg));
		printf("Child- Array in ascendng order from parent:\n");
		for(int i=0; i<n; i++)
		{
			printf("%d\n", p1rmsg[i]);
			p2wmsg[i] = p1rmsg[i];	// copy to p2wmsg
		}
		// sort array in descending order
		int i, j, x;
		for(i=1; i<n; i++)
		{
			x = p2wmsg[i];
			j = i-1;
			while(j >= 0 && p2wmsg[j] < x)
			{
				p2wmsg[j+1] = p2wmsg[j];
				j--; 
			}
			p2wmsg[j+1] = x;
		}
		// write array in descending order to pipe2
		write(pipe2des[1], p2wmsg, sizeof(p2wmsg));
	}
	return 0;
}
