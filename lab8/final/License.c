#include<stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define number_of_licenses 5
#define number_of_users 10

sem_t license, mutex;

void Request_license(int User_no)
{
	sem_wait(&mutex);
	printf("\nUser %d is requesting for license\n", User_no);
	sem_wait(&license);
	printf("\nUser %d GOT the license\n", User_no);
	sem_post(&mutex);
}

void Release_license(int User_no)
{
	printf("\nUser %d is releasing License\n", User_no);
	sem_post(&license);
	printf("\nUser %d LEFT the license\n", User_no);
}

void *Online_user(void *arg)
{
	int *u = arg;
	while(1)
	{
		Request_license(*u);
		sleep(1);
		Release_license(*u);
	}
}

int main(void)
{

	sem_init(&mutex, 0, 1);
	
	sem_init(&license, 0, number_of_licenses);
	
	pthread_t tid[number_of_users];
	
	int abc[number_of_users];
	for (int i = 0; i < number_of_users; ++i)
	{
		abc[i]=i;
		printf("\nUser %d is online \n", abc[i]);
		pthread_create(&tid[i],NULL, Online_user, &abc[i]);
	}
	for (int i = 0; i < number_of_users; ++i)
	{
		pthread_join(tid[i],NULL);
	}

	return(0);
}