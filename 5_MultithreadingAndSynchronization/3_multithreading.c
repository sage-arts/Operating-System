#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// structure with integer array and an integer variable (for array size)
// by array size we mean number of elements in the array
struct arg_struct
{
	int a[1000];
	int n;
};

void *thread_fn(void *arguments)
{
	// the array and its size is passed from the main process as arguments 
	// arguments is void pointer, cast to (struct arg_struct*)
	struct arg_struct* args = (struct arg_struct*) arguments;
	// we can dereference args to get array element at i as args->a[i] and
	// array size as args->n
	int sum = 0;
	// we need to return reference to the local variable sum
	// but it will be deallocated
	// so dynamically allocate the pointer to return
	int* res = malloc(sizeof(int));
	// calculate the sum of array elements
	for(int i=0; i<args->n; i++)
	{
		sum += args->a[i];
	}
	*res = sum;	// update value of res with sum
	// destroy the thread and pass res casted to (void*) to the return value
	// we can also use return (void*)res;
	pthread_exit((void*)res);
}

int main()
{
	pthread_t t;
	int* retval;	
	struct arg_struct args;
	printf("Enter the number of elements in the array (more than or equal to 2): ");
	scanf("%d", &args.n);
	while(args.n<2)
	{
		printf("Please enter a number more than or equal to 2: ");
		scanf("%d", &args.n);
	}
	printf("Enter the elements of the array:\n");
	for(int i=0; i<args.n; i++)
	{
		scanf("%d", &args.a[i]);
	}
	// create thread with thread id t 
	// the thread t will begin execution at the function thread_fn
	// structure args contains the array and its size which are passed to 
	// thread_fn by passing a pointer to the structure args 
	// i.e. pass by reference and cast to (void*)
	pthread_create(&t, NULL, thread_fn, (void*)&args);
	// join the thread t i.e. wait for the thread t to complete
	// &retval is reference to a pointer i.e. double pointer
	// hence the cast (void**)
	pthread_join(t, (void**)&retval);
	// now the return value of thread_fn is passed to retval
	// dereference retval to get the result (sum)
	printf("Sum of the array elements: %d\n", *retval);
	free(retval);
	return 0;
}
