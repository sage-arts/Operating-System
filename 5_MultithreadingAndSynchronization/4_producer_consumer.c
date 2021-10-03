#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define N 12	// size of the buffer

int buffer[N];	// bounded buffer
int count = 0;
// counting semaphores empty and full
// empty- number of empty slots in the buffer
// full- number of filled slots in the buffer
sem_t empty, full;
// mutex or binary semaphore with an ownership restriction 
// i.e. can by unlocked (the post operation) only by whoever locked it 
// (the wait operation)
// used to acquire and release the lock
pthread_mutex_t l;

void *producer()
{
	int item;
	while(1)
	{
		// produce item 
		item = rand()%1000;				// random number 0-999
		// getting random number as item is just example
		// you can adjust sleep time to make producer slower or faster
		// to represent the computational power used for production
		sleep(1);
		// wait operation on empty
		// i.e. wait until empty>0 and then decrement empty
		sem_wait(&empty);
		// acquire lock
		pthread_mutex_lock(&l);
		// Uncomment to see some insight
		//printf("Producer: Insert item %d at position %d\n", item, count);
		// insert item
		buffer[count] = item;
		count++;
		// release lock 
		pthread_mutex_unlock(&l);
		// post operation on full
		// increment full
		sem_post(&full);
	}
	return NULL;
}

void *consumer()
{	
	int item;
	while(1)
	{
		// wait operation on full
		// i.e. wait until full>0 and then decrement full
		sem_wait(&full);
		// acquire lock
		pthread_mutex_lock(&l);
		// remove item
		count--;
		item = buffer[count];
		// Uncomment to see some insight
		//printf("Consumer: Removed item %d from position %d\n", item, count);
		// release lock
		pthread_mutex_unlock(&l);
		// post operation on empty
		// increment empty
		sem_post(&empty);
		// consume item 
		printf("Consumed: %d\n", item);	// print item
		// printing item is just example
		// you can adjust sleep time to make consumer slower or faster
		// to represent the computational power used for consumption
		sleep(1);
	}
	return NULL;
}

int main()
{
	// initialise empty to N (initially N empty slots)
	sem_init(&empty, 0, N);
	// initialise full to 0 (initially 0 filled slots)
	sem_init(&full, 0, 0);
	pthread_mutex_init(&l, NULL);
	pthread_t th_producer, th_consumer;
	// create producer thread
	// it will begin execution at the function producer
	pthread_create(&th_producer, NULL, producer, NULL);
	// create consumer thread
	// it will begin execution at the function consumer
	pthread_create(&th_consumer, NULL, consumer, NULL);
	// join producer thread i.e. wait for producer thread to complete
	pthread_join(th_producer, NULL);
	// join consumer thread i.e. wait for consumer thread to complete
	pthread_join(th_consumer, NULL);
	// destroy empty
	sem_destroy(&empty);
	// destroy full
	sem_destroy(&full);
	// destroy l
	pthread_mutex_destroy(&l);
	return 0;
}
