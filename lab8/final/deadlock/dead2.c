#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>     


#define SNAME "/abcd"
#define SEM_NAME "/abc"

sem_t *g,*h;

void leave(){	
	int p;
	sem_getvalue(g,&p);
	printf("\nReleasing Lock mutex1 =%d\n",p);
	sem_post(g);
	sem_getvalue(g,&p);
	printf("\nReleasing Lock mutex1 = %d\n",p);
	
	sem_getvalue(h,&p);
	printf("\nReleasing Lock mutex2 =%d\n",p);
	sem_post(h);
	sem_getvalue(h,&p);
	printf("\nReleasing Lock mutex2 = %d\n",p);
	

	sem_unlink(SNAME);
	sem_unlink(SEM_NAME);

	exit(0);

}

int main()
{

	signal(SIGINT, leave);
	
	sem_t *mutex1 = sem_open(SNAME, O_CREAT, 0644, 1); 

	g = mutex1;

	printf("Created Mutex2\n");

	sleep(2);

	sem_t *mutex2 = sem_open(SEM_NAME, 0);
	h = mutex2;
	printf("Opened it\n");

	sem_wait(mutex1);

	printf("Accquiring it\n");
	
	sleep(3);
	sem_wait(mutex2);

	printf("Done\n");

	sleep(2);

	sem_post(mutex2);
	sem_post(mutex1);

	

	return 0;
}