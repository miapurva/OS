#include "fcfs_sjf.h"
#include <iostream>
using namespace std;

void fcfs_sjf_h::sjf()
{
	int n=5;
	int index;
	float sum_wait=0;
	for(int i=0; i<5; i++)
	{
		cout<<"Enter the process ID:\t";
		cin>>pid[i];
		cout<<"Enter the arrival time:\t";
		cin>>arrival_Time[i];
		cout<<"Enter the Burst time:\t";
		cin>>burst_Time[i];
	}

	for(int i=0; i<n; i++)
	{
		check[i]=0;
	}

	cout<<"PID  Arrival Time   Burst Time  Completion Time  Turn Around Time  Waiting Time \n";
	for (int i = 0; i < n; i++)
	{
		int mina=100;
		int minie=100;
		for(int j=0;j<n;j++)
		{
			if((i==0) && (check[j]==0) && (arrival_Time[j]<minie))
			{
				minie=arrival_Time[j];
				index=j;
			}
			else if((i!=0)&&(check[j]==0) && (burst_Time[j]<mina))
			{
				mina=burst_Time[j];
				index=j;
			}
		}
		int CT;
		check[index]=1;
		if(i==0)
		{
			completion_Time[index]=arrival_Time[index]+burst_Time[index];
			//check[i]=1;
		}
		else
		{
			completion_Time[index]=CT+burst_Time[index];
			//check[i]=1;
		}
		
		CT=completion_Time[index];
		turn_Around_Time[index]=completion_Time[index]-arrival_Time[index];
		waiting_Time[index]=turn_Around_Time[index]-burst_Time[index];
		sum_wait+=waiting_Time[index];
		cout<<pid[index]<<"\t "<<arrival_Time[index]<<" \t\t"<<burst_Time[index]<<" \t\t"<<completion_Time[index]<<" \t\t"<<turn_Around_Time[index]<<" \t\t"<<waiting_Time[index]<<"\n";
	}
	cout<<"Average waiting time:\t "<<(sum_wait/n);

}