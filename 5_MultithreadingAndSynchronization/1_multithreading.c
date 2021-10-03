#include <stdio.h>
#include <pthread.h>

int sum[5];	// strore the partial sums

void *thread_fn(void *arg)
{
	// calculate sum of 200 numbers starting from 200*id and store in 
	// sum[id], where id is taken as argument
	// arg is void pointer, typecast to integer pointer and dereference
	int id = *(int*)arg, i = 0;
	while(i<200)
	{
		sum[id] += 200*id+i;
		i++;
	}
	return NULL;
}

int main()
{
	pthread_t t1, t2, t3, t4, t5;
	int a1 = 0, a2 = 1, a3 = 2, a4 = 3, a5 = 4;	// arguments
	// create five threads with thread ids t1, t2, t3, t4, t5 
	// each thread will begin execution at the function thread_fn
	// so t1 finds sum of numbers from 0 to 199 in sum[0]
	// t2 from 200 to 399 in sum[1]
	// t3 from 400 to 599 in sum[2]
	// t4 from 600 to 799 in sum[3]
	// t5 from 800 to 999 in sum[4]
	pthread_create(&t1, NULL, thread_fn, (void*)&a1);
	pthread_create(&t2, NULL, thread_fn, (void*)&a2);
	pthread_create(&t3, NULL, thread_fn, (void*)&a3);
	pthread_create(&t4, NULL, thread_fn, (void*)&a4);
	pthread_create(&t5, NULL, thread_fn, (void*)&a5);
	// join the threads i.e. wait for the threads to complete
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	// add partial sums and print the total sum
	printf("Sum of first 1000 numbers (0 to 999): %d\n", sum[0]+sum[1]+sum[2]+sum[3]+sum[4]);
	return 0;
}
