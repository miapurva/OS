#include <iostream>
#include "header.h"
#include <time.h>
#include <cstdlib>
#include <algorithm>

using namespace std; 



int main()
{
	srand(time(NULL));
	int pid[6]={1,2,3,4,5}, at[5]={1,3,5,5,7}, bt[5]={2,4,3,1,5};
	
	
	/*for(int i=0;i<5;i++)
	{
		
		at[i] = rand()%10 + 1;
		bt[i] = rand()%10 + 1;

	}*/


	rr_gen(pid,at,bt);
	
	return 0;
}