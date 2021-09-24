#include <stdio.h>
#include <math.h>		// use -lm flag with gcc
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
		while(p1wmsg[i] < 0)
		{
			printf("Please enter a non-negative number\n");
			scanf("%d", &p1wmsg[i]);
		}
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
		// write array to pipe1
		write(pipe1des[1], p1wmsg, sizeof(p1wmsg));
		// read binary array(0 - not Armstrong, 1 - Armstrong) from pipe2
		read(pipe2des[0], p2rmsg, sizeof(p2rmsg));
		printf("Parent- Armstrong check using binary array from child:\n");
		for(int i=0; i<n; i++)
		{
			if(p2rmsg[i] == 1)
			{
				printf("%d is Armstrong Number (%d)\n", p1wmsg[i], p2rmsg[i]);
			}
			else
			{
				printf("%d is not Armstrong Number (%d)\n", p1wmsg[i], p2rmsg[i]);
			}
		}
	}
	// child process
	else 
	{
		close(pipe1des[1]);	// close pipe1 unwanted write side
		close(pipe2des[0]);	// close pipe2 unwanted read side
		// read array from pipe1
		read(pipe1des[0], p1rmsg, sizeof(p1rmsg));
		// create binary array(0 - not Armstrong, 1 - Armstrong)
		// for each number in given array  
		for(int i=0; i<n; i++)
		{
			int x = p1rmsg[i], order = 0, sum = 0;
			// calculate order(no. of digits in the number)
			while(x)
			{
				order++;
				x /= 10;
			}
			x = p1rmsg[i];
			// calculate sum of digits raised to the power of order
			while(x)
			{
				int r = x%10;
				sum += pow(r, order);
				x /= 10;
			}
			// this sum is same as original number -> (1 - Armstrong)
			if(sum == p1rmsg[i])
			{
				p2wmsg[i] = 1;	// put 1 in binary array
			}
			// otherwise -> (0 - not Armstrong)
			else
			{
				p2wmsg[i] = 0;	// put 0 in binary array
			}
		}
		// write binary array(0 - not Armstrong, 1 - Armstrong) to pipe2
		write(pipe2des[1], p2wmsg, sizeof(p2wmsg));
	}
	return 0;
}
