#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

#define NUM_SAVAGES 3

sem_t emptyPot;
sem_t fullPot;

void *savage (void*);
void *cook (void*);

static pthread_mutex_t print_mutex;

static int servings = 15;

int getServingsFromPot(int savage_id)
 {

    if (servings > 0) 
    {
        servings--;
        printf("-------serving%d------\n",servings);     
        
        sleep(2);

        pthread_mutex_lock (&print_mutex);
        printf ("Savage: %i is DONE eating\n", savage_id);
        pthread_mutex_unlock (&print_mutex);   //signaling the cook
       
    } 
}

void putServingsInPot () {

    servings =15;
    sem_post (&fullPot);

}

void *cook (void *id)
 {
    int cook_id = *(int *)id;
    int i;

    while ( 1 ) 
    {

        sem_wait (&emptyPot); //waiting for signal

        putServingsInPot ();

        pthread_mutex_lock (&print_mutex);
        printf ("\nCook filled pot\n\n");
        pthread_mutex_unlock (&print_mutex);


    }
    pthread_exit(0);
    return NULL;
}

void *savage (void *id) 
{
    int savage_id = *(int *)id;
    int myServing;

  //printf("Hello Savage---> %d\n", savage_id);
    sleep(2);

    while (1)             
     {

        if (servings == 0)            
        {
            sem_post (&emptyPot);          //signaling the cook
            sem_wait (&fullPot);          //waiting for cook to fill the pot
            
        }
	  pthread_mutex_lock (&print_mutex);
        printf ("Savage: %d is eating\n", savage_id); 
        pthread_mutex_unlock (&print_mutex);          //to ensure more than one savage can eat 

	  getServingsFromPot(savage_id);
		       
        
    }
    pthread_exit(0);
    return NULL;
}

int main() {

    int i, id[NUM_SAVAGES+1];
    pthread_t tid[NUM_SAVAGES+1];

    // Initialize the mutex locks
    pthread_mutex_init(&print_mutex, NULL);

    // Initialize the semaphores
    sem_init(&emptyPot, 0, 0);
    sem_init(&fullPot,  0, 0);

    for (i=0; i<NUM_SAVAGES; i++) 
    {
        id[i] = i;
        printf("Savage %d entered \n", id[i]);
        pthread_create (&tid[i], NULL, savage, (void *)&id[i]);
    }
        
    pthread_create (&tid[i], NULL, cook, (void *)&id[i]);

    for (i=0; i<NUM_SAVAGES; i++)
        pthread_join(tid[i], NULL);

}
