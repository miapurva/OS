#include <stdio.h>
#include <stdlib.h>


#define P_COUNT 7
#define R_COUNT 3

int main(){
	
	int current[P_COUNT][R_COUNT] = {
		{1,2,3},
		{3,0,4},
		{6,1,1},
		{3,4,1},
		{4,3,2},
		{5,2,1},
		{2,1,1}
	};

	int max[P_COUNT][R_COUNT] = {
		{2,4,5},
		{1,1,5},
		{5,3,4},
		{3,4,2},
		{1,4,4},
		{2,3,2},
		{4,2,2}
	};

	int avail[R_COUNT] = {1,1,1};

	int i,j;
	printf("Total Capacity:\n");
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
	printf("Safe Seq.:\n");
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
				printf(" %d ", i );
				avail[0] += current[i][0];
				avail[1] += current[i][1];
				avail[2] += current[i][2];

				current[i][0] = -100;
				current[i][1] = -100;
				current[i][2] = -100;

				}
		}
	}
	printf("\n");
	return 0;

}
