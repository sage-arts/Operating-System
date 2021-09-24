#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

#define shmsize 1024

int main()
{
	int shmid;
	void *SM;	// declared as void*, typecast to int* or char* as needed
	// get the shared memory created by P1 with key 2914
	if((shmid = shmget((key_t)2914, shmsize, 0666)) < 0)
	{
		printf("Error in shmget\nTry running P1 first\n");
		exit(1);	// EXIT_FAILURE
	}
	// attach the shared memory to P2's address space
	if((SM = shmat(shmid, NULL, 0)) == (char*)-1)
	{
		printf("Error in shmat\n");
		exit(1);	// EXIT_FAILURE
	}
	// Note no system call required for read write as this shared memory 
	// is attached to our address space
	// read the string that P1 wrote to the shared memory
	char *buf = (char*)SM;
	printf("String that P1 wrote to the shared memory: %s\n", buf);
	int n = strlen(SM);
	// get reverse of this string
	char rev[n];
	for(int i=0; i<n; i++)
	{
		rev[i] = buf[n-i-1];
	}
	// palindrome check result 1 - palindrome, 0 - not palindrome
	int res = 1;				// set result to 1
	// compare reverse string and original string character by character
	for(int i=0; i<n; i++)
	{
		// if mismatch
		if(rev[i] != buf[i])		// note: case sensitive comparision is used 
		{
			res = 0;		// set result to 0
			break;			// stop
		}
	}
	// write result to the shared memory
	*(int*)SM = res;
	printf("Written %d to the shared memory\n", *(int*)SM);
	// detach the shared memory from P2's address space
	shmdt(SM);
	exit(0);
}
