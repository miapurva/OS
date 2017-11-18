#include <iostream>
#include <cstdlib>
#define size 5
using namespace std;

int completion_Time[size], turn_Around_Time[size], waiting_Time[size];


int compare(const void * a , const void * b){

	return (*(int*)a - *(int*)b );

}

void rr_gen(int pid[] , int arrival_Time[] , int burst_Time[]){
	
	int temp;
	float sum_wait=0;
	qsort(arrival_Time,size,sizeof(int),compare);

	cout<<"Arrival Time: \n";
	for (int d = 0; d < size; ++d)
		{
			cout<<arrival_Time[d]<<endl;
		}
		cout<<"\nBurst Time:\n";
	for (int d = 0; d < size; ++d)
		{
			cout<<burst_Time[d]<<endl;
		}
		cout<<endl;

	int tq = 3;
	int pq[size]={100,100,100,100,100};
	int qq[200] = {100} ,front=0,rear=0;
	
	qq[0] = 0;
	front++;
	pq[0] = burst_Time[0];
	int last = 0,index=0;
	
	int pending	= 1;
	int current = 1;
	int remaining = 200;	

	for (int i = arrival_Time[0]; pending != 0; i = i+tq)
	{   

		tq=2;
		
		for (int d = 0; d < size; ++d) // to check for arriving processes 
		{
			if (arrival_Time[d] <= i && pq[d] == 100 )
				{
					pq[d] = burst_Time[d];
					qq[front] = d;
					front++;	
				}	
		}

		if (remaining != 200)
		{
			qq[front] = remaining;
			front++;
			remaining=200;
		}
		
		for (int d = 0; d < size; ++d) // to check for completed processes
		{
			if (pq[d] == 0)
				{
					pq[d] = 101;
					completion_Time[d] = i;
					turn_Around_Time[d] = completion_Time[d] - arrival_Time[d];
					waiting_Time[d]=turn_Around_Time[d]-burst_Time[d];
					sum_wait+=waiting_Time[d];
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

			index = qq[rear];

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

	cout<<"\n\t\t\t\t\t\tRound Robin: ";
	cout<<"\n\t\t\t\t\t\t------------";

	cout<<"\n\tPID\tArrival Time\t Burst Time \tCompletion Time TurnAround Time Waiting Time\n";
	for (int i = 0; i < size; ++i)
	{
		cout<<"\n\t"<<pid[i]<<"\t|\t"<<arrival_Time[i]<<"\t|\t"<<burst_Time[i]<<"\t|\t"<<completion_Time[i]<<"\t|\t"<<turn_Around_Time[i]<<"\t|\t"<<waiting_Time[i]<<endl;

	}
	cout<<"\n Average Waiting Time:\t"<<(sum_wait)/size;
	cout<<endl;

}