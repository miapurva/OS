#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_SAVAGES 3

sem_t empty_pot,full_pot;
static pthread_mutex_t servings_mutex;
static pthread_mutex_t print_mutex;
static int servings=5;

void *Savage(void *id)
{
	int savage_id=*(int *)id;

	while(1)
	{
		pthread_mutex_lock(&servings_mutex);
		if(servings==0)
		{
			sem_post(&empty_pot);
			printf("\nSavage %d signalled the cook\n", savage_id);
			

			sem_wait(&full_pot);
			servings=5;
		}
		servings--;
		printf("Servings--->%d\n", servings);

		pthread_mutex_lock(&print_mutex);
		printf("Savage %d is eating\n", savage_id);
		pthread_mutex_unlock(&print_mutex);


		pthread_mutex_unlock(&servings_mutex);
		sleep(2);
		

		pthread_mutex_lock(&print_mutex);
		printf("Savage %d is DONE eating\n", savage_id);
		pthread_mutex_unlock(&print_mutex);


	}
	pthread_exit(0);
}


void Cook(void *cid)
{
	while(1)
	{
		sem_wait(&empty_pot);
		//printf("0Servings--->%d\n",servings);
		printf("\nCook filled the pot\n\n");
		//servings=5;
		sem_post(&full_pot);
	}
	
	pthread_exit(0);
}

int main(void)
{
	int i, id[NUM_SAVAGES+1];
    pthread_t tid[NUM_SAVAGES+1];

    pthread_mutex_init(&servings_mutex,NULL);
    pthread_mutex_init(&print_mutex,NULL);

    // Initialize the semaphores
    sem_init(&empty_pot, 0, 0);
    sem_init(&full_pot,  0, 0);

    for (i = 0; i < NUM_SAVAGES; ++i)
    {
    	id[i]=i;
    	pthread_create(&tid[i],NULL,(void *)Savage,(void *)&id[i]);
    }
    pthread_create(&tid[i],NULL,(void *)Cook,(void *)&id[i]);

    for (i=0; i<NUM_SAVAGES; i++)
        pthread_join(tid[i], NULL);
    pthread_join(tid[i],NULL);
	return(0);
}