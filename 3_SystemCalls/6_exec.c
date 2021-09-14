#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("Redirecting to Twitter from your firefox browser\n");
	// first and second arguments as path of executable file
	// terminated by NULL
     	execl("/usr/bin/firefox", "/usr/bin/firefox", "twitter.com", NULL);
     	return 0;
}
