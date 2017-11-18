#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <signal.h>

#define SNAME "/abc"
#define SEM_NAME "/abcd"


sem_t *g;
/*
void leave(){	
	int p;
	sem_getvalue(g,&p);
	printf("\nReleasing Lock: mutex1 = %d\n",p);
	sem_post(g);
	sem_getvalue(g,&p);
	printf("\nReleasing Lock: mutex1 = %d\n",p);

	sem_unlink(SNAME);

	exit(0);

}
*/
int main()
{

	//signal(SIGINT, leave);
	
	sem_t *mutex1 = sem_open(SNAME, O_CREAT, 0644, 1); 

	// g = mutex1;

	printf("Created Mutex1\n");

	sleep(2);

	sem_t *mutex2 = sem_open(SEM_NAME, 0); 

	printf("Opened it\n");


	sem_wait(mutex1);

	sleep(3);

	printf("Accquiring it\n");
	sem_wait(mutex2);

	printf("Done\n");
	sleep(2);

	sem_post(mutex2);
	sem_post(mutex1);


	return 0;
}
