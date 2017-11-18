#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE1 3
#define SIZE2 3
#define SIZE3 3

int res[SIZE1][SIZE3];

typedef struct Submat
{
	int row;
	int column;
	int row1[SIZE1];
	int column2[SIZE2];
}submat;

void *mul(void *r)
{
	int sum=0;
	submat *d=(submat *)r;

	for (int i = 0; i < SIZE2; i++)
	{
		sum=sum + d->row1[i] * d->column2[i];
	}
	//result[d->row][d->column]=sum;
	res[d->row][d->column]=sum;
	pthread_exit(0);

}

int main(void)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//pthread_attr_setschedpolicy(&attr,SCHED_OTHER);

	pthread_t t[SIZE1];

	int a[SIZE1][SIZE2]={
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};
	int b[SIZE2][SIZE3]={
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};

	submat result[SIZE1][SIZE3];

	for (int i = 0; i < SIZE1; ++i)
	{
		for (int j = 0; j < SIZE3; ++j)
		{
			for (int k = 0; k < SIZE2; ++k)
			{
				result[i][j].row=i;
				result[i][j].column=j;
				result[i][j].row1[k] = a[i][k];
	  			result[i][j].column2[k] = b[k][j];

			}
			pthread_create(&t[i],&attr,mul,&result[i][j]);
		}
	}

	for (int i = 0; i < SIZE1; ++i)
	{
		pthread_join(t[i],NULL);
	}

	printf("\nInput 1: \n");
	for(int i=0 ; i<SIZE1 ; i++){
	
		for(int j=0 ; j<SIZE3; j++){
			
			printf(" %d ",a[i][j]);
		
		}
		
		printf("\n");	
	}

	printf("\nInput 2: \n");
	for(int i=0 ; i<SIZE1 ; i++){
	
		for(int j=0 ; j<SIZE3; j++){
			
			printf(" %d ",b[i][j]);
		
		}
		printf("\n");	
	}

	printf("\nResult: \n");
	for(int i=0 ; i<SIZE1 ; i++)
	{
		for(int j=0 ; j<SIZE3; j++)
		{
			printf(" %d ",res[i][j]);
		}
		printf("\n");	
	} 		

	return(0);
}