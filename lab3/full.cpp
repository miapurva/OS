#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "priority_pe.h"
using namespace std;

class priority_pe
{

private:
//int n;
int pid[10];
int turn_Around_Time;
int waiting_Time[10];
int arrival_Time[10];
int burst_Time[10];
int remain_Time[10];
int priorityarray[10];
public:
void priority();

};

void priority_pe::priority()
{
	srand(time(NULL));
	int n,temp;
	cout<<"Enter the number of processes:\n";
	//cin>>n;
	n=rand()%7;
	cout<<n<<endl;

	for(int i=0;i<n;i++)
	{
		pid[i]=i+1;
		//cout<<"Enter the arrival time:\t";
		//cin>>arrival_Time[i];
		arrival_Time[i]=rand()%15;
		//cout<<"Enter the burst time:\t";
		//cin>>burst_Time[i];
		priorityarray[i]=rand()%15;
		burst_Time[i]=rand()%15;

		remain_Time[i]=burst_Time[i];

	}
	//Sorting
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n-1-i; j++)
		{
			if(arrival_Time[j]>arrival_Time[j+1])
			{
				temp=arrival_Time[j];
				arrival_Time[j]=arrival_Time[j+1];
				arrival_Time[j+1]=temp;

				temp=burst_Time[j];
				burst_Time[j]=burst_Time[j+1];
				burst_Time[j+1]=temp;

				temp=remain_Time[j];
				remain_Time[j]=remain_Time[j+1];
				remain_Time[j+1]=temp;

				temp=priorityarray[j];
				priorityarray[j]=priorityarray[j+1];
				priorityarray[j+1]=temp;

				temp=pid[j];
				pid[j]=pid[j+1];
				pid[j+1]=temp;
			}
		}
	}
	cout<<"PID  Arrival Time   Burst Time  Priority\n";
for (int i = 0; i < n; ++i)
{
		cout<<pid[i]<<" \t"<<arrival_Time[i]<<" \t\t"<<burst_Time[i]<<" \t\t"<<priorityarray[i]<<"\n";

}

	int remain=0,sum_wait=0, end_Time, smallest;
	//cout<<"\n\nProcess Finish\t| Completion Time | Turnaround Time | Waiting Time\n\n";
	cout<<"\n\nArrival Time\t|  Burst Time  | Priority | Completion Time | Turnaround Time | Waiting Time\n\n";

	int process_f=0;

	for (int time = 0; remain!= n; time++)
	{
		//cout<<"hi1";
		smallest=9;
		for (int j = 0; j < n; ++j)
		{
			if((remain_Time[j]>0) && (arrival_Time[j]<=time) && (priorityarray[j]>priorityarray[smallest]))
				smallest=j;
		}
		remain_Time[smallest]--;
		if(remain_Time[smallest]==0)
		{
			pid[smallest]=smallest+1;
			remain++;
			//calculation
			end_Time=time+1;
			turn_Around_Time= end_Time- arrival_Time[smallest];
			waiting_Time[smallest]= turn_Around_Time- burst_Time[smallest];
			//cout<<"\n\tP["<<pid[smallest]<<"]\t|\t"<<end_Time<<"\t|\t"<<turn_Around_Time<<"\t|\t"<<waiting_Time[smallest];
			cout<<"\n\t"<<arrival_Time[smallest]<<"\t|\t"<<burst_Time[smallest]<<"\t|\t"<<priorityarray[smallest]<<"\t|\t"<<end_Time<<"\t|\t"<<turn_Around_Time<<"\t|\t"<<waiting_Time[smallest];
			sum_wait+=turn_Around_Time -burst_Time[smallest];
		}
	}
	cout<<"\n\nAverage waiting time ="<<sum_wait*1.0/n;
	cout<<endl;
}

int main(void)
{
	int n=5;
	priority_pe s;
	
	s.priority();

	return 0;
}