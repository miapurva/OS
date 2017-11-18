#include <iostream>
#include <cstdlib>
#include "header.h"
using namespace std;

#define size 6

int round:: compare(const void * a , const void * b)
{

	return (*(int*)a - *(int*)b );

}

void round::roundrobin()
{
	
	int temp;
	qsort(arrival_Time,size,sizeof(int),compare);

	cout<<"\nArrival "<<endl;
	for (int d = 0; d < size; ++d)
		{
			cout<<arrival_Time[d];
		}
		cout<<"\n Burst\n";
	for (int d = 0; d < size; ++d)
		{
			cout<<burst_Time[d];
		}
		cout<<endl;

	int tq;
	int pq[size]={100,100,100,100,100,100};
	int rq[200] = {100} ,front=0,rear=0;
	
	rq[0] = 0;
	front++;
	pq[0] = burst_Time[0];
	int last = 0,index=0;
	
	int pending	= 1;
	int current = 1;
	int remaining = 200;	

	for (int time = arrival_Time[0]; pending != 0; time = time+tq)
	{   

		tq=3;
		
		for (int d = 0; d < size; ++d) // to check for arriving processes 
		{
			if (arrival_Time[d] <= time && pq[d] == 100 )
				{
					pq[d] = burst_Time[d];
					rq[front] = d;
					front++;	
				}	
		}

		if (remaining != 200)
		{
			rq[front] = remaining;
			front++;
			remaining=200;
		}
		
		for (int d = 0; d < size; ++d) // to check for completed processes
		{
			if (pq[d] == 0)
				{
					pq[d] = 101;
					completion_Time[d] = time;
					turn_Around_Time[d] = completion_Time[d] - at[d];
					waiting_Time[d]=turn_Around_Time[d]-burst_Time[d];
				}	
		}

		int u = 0;
		for (int d = 0; d < size; ++d) // to check for current processes 
		{
			if (pq[d] != 100 && pq[d] != 101)
				{
					u++;
				}	
		}

		pending = u;


 		if(u==0){
			//printf("\n\nNo more processes!\n\n");
			break;
		}
		else{
			
			//decide which process will be executed next based on queue

			index = rq[rear];


			temp = pq[index] - tq;

			if(temp <= 0){
				temp = 0;
				tq = pq[index];
				
			}
			else{
				remaining = index;
				
			}
			rear++;
			pq[index]=temp;
			
				
		}
		
	}

	cout<<"Gantt Chart: ";
	for (int d = 0; d < front; ++d)
		{
			cout<<"%d  ", rq[d];
		}

	cout<<"\nRound Robbin Schedule: ";
	cout<<"\n-----------------------";
	
	
		for (int i = 0; i < size; ++i)
		{
			cout<<"\nProcess ID: %d", pid[i];
			cout<<"\tArrival Time: %d", arrival_Time[i];
			cout<<"\tBurst Time: %d", burst_Time[i];
			cout<<"\tCompletion Time: %d", completion_Time[i];
			cout<<"\tTurn-around Time: %d", turn_Around_Time[i];
			cout<<"\tWaiting Time: %d", waiting_Time[i];
		}
	
	cout<<"\n";
}