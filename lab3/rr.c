#include <stdio.h>
#include <stdlib.h>
#define size 6
using namespace std;

int completion_Time[size], turn_Around_Time[size], waiting_Time[size];


int compare(const void * a , const void * b){

	return (*(int*)a - *(int*)b );

}

void rr_gen(int pid[] , int arrival_Time[] , int burst_Time[]){
	
	int temp;
	
	qsort(arrival_Time,size,sizeof(int),compare);

	cout<<"Arrival Time: \n";
	for (int d = 0; d < size; ++d)
		{
			cout<<arrival_Time[d];
		}
		cout<<"\nBurst Time:\n";
	for (int d = 0; d < size; ++d)
		{
			cout<<burst_Time[d];
		}
		cout<<endl;

	int tq = 3;
	int pq[size]={100,100,100,100,100,100};
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

		tq=3;
		
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
			qq[v] = remaining;
			v++;
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

	/*cout<<"Gantt Chart: ";
	for (int d = 0; d < v; ++d)
		{
			cout<<qq[d];
		}
*/
	cout<<"\nRound Robin: ";
	cout<<"\n------------";
	
	
		for (int i = 0; i < size; ++i)
		{
			cout<<"\nProcess ID: "<<pid[i];
			cout<<"\tArrival Time: "<< arrival_Time[i];
			cout<<"\tBurst Time: "<< burst_Time[i];



			cout<<"\tCompletion Time: "<<completion_Time[i];
			cout<<"\tTurn-around Time: "<< turn_Around_Time[i];
			cout<<"\tWaiting Time: "<< waiting_Time[i];
		}
	
	cout<<endl;



}