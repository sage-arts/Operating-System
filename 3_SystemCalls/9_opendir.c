// Aman Sharma
// CED19I054

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main()
{
	char dir_path[100];
	DIR *dir_stream;
	struct dirent *dir_entry;
	printf("Enter the path of a directory:\n");
	scanf("%s", dir_path); 
	errno = 0;
	// create directory stream representing the directory given by dir_path
	if((dir_stream = opendir(dir_path)) == NULL)
	{
		// error handling
		switch(errno)
		{
			case EACCES:
				printf("Permission denied\n");
				break;
			case ENOENT:
				printf("No such directory\n");
				break;
			case ENOTDIR:
				printf("%s is not a directory\n", dir_path);
				break;
		}
		exit(1);
	}
	printf("Entries in your directory:\n");
	// successively invoke readdir until the entire directory is read 
	// i.e. readdir returns NULL
	// get the entries in the dirent structure dir_entry 
	while((dir_entry = readdir(dir_stream)) != NULL)
	{
		// d_name field has the name of a single entry(file or 
		// subdirectory) within the directory
		printf("%s\n", dir_entry->d_name);
	}
	// close the directory stream
	closedir(dir_stream);
	exit(0);
}
