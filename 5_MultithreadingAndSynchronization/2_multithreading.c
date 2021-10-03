#include <stdio.h>
#include <pthread.h>

void *thread_fn(void *arg)
{
	// print numbers from 0 to n
	// where n is passed from the main process as argument
	// arg is void pointer, typecast to integer pointer and dereference
	int n = *(int*)arg;
	printf("Numbers from 0 to %d:\n", n);
	for(int i=0; i<=n; i++)
	{
		printf("%d\n", i);
	}
	return NULL;
}

int main()
{
	pthread_t t;
	int n;
	printf("Enter the value of n: ");
	scanf("%d", &n);
	// create thread with thread id t 
	// the thread t will begin execution at the function thread_fn
	// to which n is passed as argument
	pthread_create(&t, NULL, thread_fn, (void*)&n);
	// join the thread t i.e. wait for the thread t to complete
	pthread_join(t, NULL);
	return 0;
}
