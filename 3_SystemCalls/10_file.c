// Aman Sharma
// CED19I054

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	char *name = "party.txt", msg[50] = "Hello it is Party Time", buff[100];
	int fd;
	// create the file if not exists given by name with permissions 0644 
	// map the file to fd, open it with read write access
	// and file position is set to zero
	fd = open(name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	// error handling
	if(fd == -1)
	{
		printf("Unable to open file\n");
		exit(1);	// EXIT_FAILURE
	}
	printf("%s opened with read write access\n", name);
	// write msg to the file
	write(fd, msg, sizeof(msg));
	printf("Message written to the file %s\n", name);
	// set file position to zero 
	// because it was updated by write
	lseek(fd, 0 , SEEK_SET);
	// read into buff from the file 
	read(fd, buff, sizeof(buff));
	printf("Displaying the file %s:\n%s\n", name, buff);
	close(fd);
	exit(0);
}
