#define BUFFER_SIZE 15
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<pthread.h>
#include<semaphore.h>
typedef int buffer_item;
#define RAND_DIVISOR 100000000
#define TRUE 1
/*mutex lock*/
pthread_mutex_t mutex;
/*the semaphores*/
sem_t full,empty;
/*the buffer*/
buffer_item buffer[BUFFER_SIZE];
/*buffer counter*/
int counter;
pthread_t tid[3];//thread id
pthread_attr_t attr;//set of thread attributes
void *prodcer(void *param);/*producer thread*/
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void *consumer(void *param);/*consumer thread*/

void initializeData()
{
	/*create the mutex lock*/
	pthread_mutex_init(&mutex,NULL);

	/*create the full semaphore and initialize to 0*/
	 sem_init(&full,0,0);
	 /*create the empty semaphore and initialize to BUFFER_SIZE*/
	 sem_init(&empty,0,BUFFER_SIZE);
	 /*get the default attribute*/
	 pthread_attr_init(&attr);
	 /*init buffer*/
	 counter=0;
}
 
//producer thread
void *producer(void *param)
{
	buffer_item item=0;
	while(TRUE)
	{
		/*sleep for a random period of time*/
		sleep(2);
		/*generate  a random number*/
		item ++;
		/*acquire the empty lock*/

		/*acquire the mutex lock*/
		pthread_mutex_lock(&mutex);
		sem_wait(&empty);
		if(insert_item(item))
		{
			fprintf(stderr,"producer report error condition\n");
		}
		else
		{
			printf("producer produced %d\n",item);
		}
		sem_post(&full);
		pthread_mutex_unlock(&mutex);

	}
pthread_exit(0);
}

/*consumer thread*/
void *consumer(void *param)
{
	buffer_item item;
	while(TRUE)
	{
		/*sleep for a random period of time*/
		//int rNum =rand()/RAND_DIVISOR;
		sleep(2);
		/*acquire the full lock*/

		/*acquire the mutex lock*/
		pthread_mutex_lock(&mutex);
		sem_wait(&full);
		if(remove_item(&item))
		{
		fprintf(stderr,"consumer report error condition\n");
		}
		else
		{
		printf("consumer consumed %d\n",item);
		}
		sem_post(&empty);

		/*release the mutex lock*/
		pthread_mutex_unlock(&mutex);
		/*signal empty*/
	}
pthread_exit(0);
}

/*add an item to the buffer*/
int insert_item(buffer_item item)
{
	/*when the buffer is not full add the item and increment the counter*/
	if(counter<BUFFER_SIZE)
	{
		buffer[counter]=item;
		counter++;
		return 0;
	}
	else
	{
		/*error the bufer is full*/
		return -1;
	}
}

/*remove an item from the buffer*/
int remove_item(buffer_item *item)
{
	/*when the buffer is not empty remove the item and decrement the counter*/
	if(counter>0)
	{
		*item=buffer[(counter-1)];
		counter--;
		return 0;
	}
	else
	{
	  /*error buffer empty*/
	    return -1;
	}
}
int main(int argc,char *argv[])
{
	/*loop counter*/
	int i;
	pthread_t c_id;
	/*verify the correct no of arguments were passed in */
	if(argc!=4)
	{
		fprintf(stderr,"USAGE:./main.out <INT> <INT> <INT>\n");
	}
	int mainSleepTime=atoi(argv[1]);/*time in seconds for main to sleep*/
	int numProd=atoi(argv[2]);/*number of producer threads*/
	int numCons=atoi(argv[3]);/*number of consumer threads*/
	/*initialize the app*/
	initializeData();
	/*create the producer threads*/
	
		printf("Hello---->0\n");
		pthread_create(&c_id,&attr,producer,NULL);
		pthread_join(c_id,NULL);
		printf("Hello---->1\n");
	/*create the consumer threads*/
	for(i=0;i<numCons;i++)
	{
		pthread_create(&tid[i],&attr,consumer,NULL);
		pthread_join(tid[i],NULL);
	}
	/*sleep for the specified amount of time in milliseconds*/
	sleep(mainSleepTime);
	/*exit program*/
	printf("exit the program\n");
	exit(0);
}
