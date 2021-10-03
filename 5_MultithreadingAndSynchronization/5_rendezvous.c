#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// At a point of execution neither of the two threads A and B is 
// allowed to proceed until both have arrived
// two semaphores 
// Aarrived- indicates whether thread A has arrived at this point
// i.e whether thread A has executed statement a1
// Barrived- indicates whether thread B has arrived at this point
// i.e whether thread B has executed statement b1
sem_t Aarrived, Barrived;

void *threadA_fn()
{
	printf("a1\n");			// statement a1
	// post operation on Aarrived
	// increment Aarrived (indicating A has arrived)
	sem_post(&Aarrived);	
	// wait operation on Barrived
	// wait until Barrived>0 (i.e. until B has arrived) 
	// and then decrement Barrived
	sem_wait(&Barrived);	
	printf("a2\n");			// statement a2
	return NULL;
}

void *threadB_fn()
{	
	printf("b1\n");			// statement b1
	// post operation on Barrived
	// increment Barrived (indicating B has arrived)
	sem_post(&Barrived);	
	// wait operation on Aarrived
	// wait until Aarrived>0 (i.e. until A has arrived) 
	// and then decrement Aarrived
	sem_wait(&Aarrived);	
	printf("b2\n");			// statement b2
	return NULL;
}

int main()
{
	// initialise Aarrived and Barrived to 0 
	// as initially neither of the two threads has arrived at the point
	// in other words both the statements a1 and b1 are to be executed
	sem_init(&Aarrived, 0, 0);
	sem_init(&Barrived, 0, 0);
	pthread_t tA, tB;
	// create thread A
	// it will begin execution at the function threadA_fn
	pthread_create(&tA, NULL, threadA_fn, NULL);
	// create thread B
	// it will begin execution at the function threadB_fn
	pthread_create(&tB, NULL, threadB_fn, NULL);
	// join thread A i.e. wait for thread A to complete
	pthread_join(tA, NULL);
	// join thread B i.e. wait for thread B to complete
	pthread_join(tB, NULL);
	// destroy Aarrived
	sem_destroy(&Aarrived);
	// destroy Barrived
	sem_destroy(&Barrived);
	return 0;
}
