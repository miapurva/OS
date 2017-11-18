#include<stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define number_of_chairs 3
#define number_of_students 5

int  CHAIR, Mode_of_TA=0;
sem_t chairs,TA;

void check()
{
	sem_getvalue(&chairs, &CHAIR);
	printf("Number of free chairs:%d\t\n", CHAIR);
	if(Mode_of_TA==0)
	{
		printf("TA is sleeping!\n");
	}
}


void Wakeup(int student)
{
	sleep(2);

	sem_wait(&chairs);
	printf("Student %d  is waiting OUTSIDE the cabin on the chair\n", student);
	sem_wait(&TA);
	sem_post(&chairs);

	Mode_of_TA=1;
	printf("TA woke up for the student: %d and is helping him\n", student);
	printf("Student %d left\n", student);
	sem_getvalue(&chairs,&CHAIR);
	if(CHAIR == number_of_chairs)
		Mode_of_TA = 0;
	
	sem_post(&TA);
	check();
}

void *Student(void *arg)
{
	int *student = arg;
	while(1)
	{
		Wakeup(*student);
	}
}

int main(void)
{
	sem_init(&TA, 0, 1);
	sem_init(&chairs, 0, number_of_chairs);
	pthread_t tid[number_of_students];

	int student_id[number_of_students];
	for (int i = 0; i < number_of_students; ++i)
	{
		student_id[i] = i + 1;
		pthread_create(&tid[i], NULL, Student, &student_id[i]);
	}
	for (int i = 0; i < number_of_students; ++i)
	{
		pthread_join(tid[i],NULL);
	}
	return(0);
}
