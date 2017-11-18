#include <stdio.h>
#include <stdlib.h>

#define P_COUNT 7
#define R_COUNT 3

#define RED     "\033[31m"
#define GREEN	"\033[32m" 
#define RESET   "\033[0m"

int main(){
	
	int current[P_COUNT][R_COUNT] = {
		{1,2,3},
		{2,0,4},
		{1,1,1},
		{3,4,1},
		{2,3,2},
		{5,2,1},
		{2,1,1}
	};

	int max[P_COUNT][R_COUNT] = {
		{3,4,5},
		{3,1,5},
		{4,3,4},
		{5,4,2},
		{3,4,4},
		{6,3,2},
		{4,2,2}
	};

	int avail[R_COUNT] = {1,1,1};

	printf("Currently Allocated: \n");

	int i,j;
	for (i = 0; i < P_COUNT; ++i)
	{
		for ( j = 0; j < R_COUNT; ++j)
		{
			printf(" %d ", current[i][j]);
		}
		printf("\n");
	}

	printf("Max Capacity: \n");

	for (i = 0; i < P_COUNT; ++i)
	{
		for ( j = 0; j < R_COUNT; ++j)
		{
			printf(" %d ", max[i][j]);
		}
		printf("\n");
	}

	printf("Remaining : \n");
	for ( j = 0; j < R_COUNT; ++j)
	{
		printf(" %d ", avail[j]);
	}
	printf("\n");

	printf("Total Capacity: \n");

	int r[R_COUNT] = {0};

	for (i = 0; i < P_COUNT; ++i)
	{
		
		r[0] += (current[i][0]);
		r[1] += (current[i][1]);
		r[2] += (current[i][2]);

	}
	r[0] += avail[0];
	r[1] += avail[1];
	r[2] += avail[2];


	for ( i = 0; i < R_COUNT; ++i)
	{
		printf("resource %d = %d \n",i+1 , r[i] );
	}

	int lim[R_COUNT];

	int k;
	for ( k = 0; k < P_COUNT; ++k)
	{
		for (i = 0; i < P_COUNT; ++i)
		{
			for ( j = 0; j < R_COUNT; ++j)
			{
					lim[j] = current[i][j] + avail[j];
			}
			int complete = 1;
			for (j = 0; j < R_COUNT; ++j)
			{
				if (lim[j] < max[i][j])
				{
					complete = 0;
				}
			}

			if (complete == 1)
			{
				printf(GREEN"\nProcess %d complete ", i );
				printf(RESET"\n");
				avail[0] += current[i][0];
				avail[1] += current[i][1];
				avail[2] += current[i][2];

				current[i][0] = -100;
				current[i][1] = -100;
				current[i][2] = -100;

				printf(RED"\nAvail : %d %d %d ", avail[0],avail[1],avail[2]);
				printf(RESET"\n");
			}
		}
	}

	return 0;

}