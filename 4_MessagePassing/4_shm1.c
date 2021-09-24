#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

#define shmsize 1024

int main()
{
	int shmid;
	void *SM;	// declared as void*, typecast to int* or char* as needed
	// create the shared memory with key 2914
	if((shmid = shmget((key_t)2914, shmsize, 0666|IPC_CREAT)) < 0)
	{
		printf("Error in shmget\n");
		exit(1);	// EXIT_FAILURE
	}
	// attach the shared memory to P1's address space
	if((SM = shmat(shmid, NULL, 0)) == (char*)-1)
	{
		printf("Error in shmat\n");
		exit(1);	// EXIT_FAILURE
	}
	// Note no system call required for read write as this shared memory 
	// is attached to our address space
	// write a string from user to the shared memory
	printf("Enter a string: ");
	scanf("%s", (char*)SM);
	printf("Written the given string to the shared memory\n");
	// wait until P2 has written palindrome check result 0 or 1 to the 	
	// shared memory
	printf("Waiting for P2 to write 0 or 1 to the shared memory\n");
	while(*(int*)SM != 0 && *(int*)SM != 1);
	// read what P2 wrote to the shared memory
	// if it is 0 then the string is not palindrome as checked by P2
	// otherwise it is 1 and the string is palindrome as checked by P2
	int res = *(int*)SM;
	printf("P2 wrote %d to the shared memory\n", res);
	if(res == 0)
	{
		printf("The given string is not palindrome\n");
	}
	else
	{
		printf("The given string is palindrome\n");
	}
	// detach the shared memory from P1's address space
	shmdt(SM);
	// destroy the shared memory
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}
