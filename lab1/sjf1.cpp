#include "fcfs_sjf.h"
#include <iostream>
using namespace std;


int fcfs_sjf_h::minimum_arrival()
{
	int minie=arrival_Time[0];
	for(int i=0;i<5;i++)
	{
		if(arrival_Time[i]<minie)
			minie=arrival_Time[i];
	}
	return (minie);
}

int fcfs_sjf_h::minimum_burst()
{
	int minie=burst_Time[0];
	for(int i=0;i<5;i++)
	{
		if(burst_Time[i]<minie)
			minie=burst_Time[i];
	}
	return (minie);
}


void fcfs_sjf_h::sjf()
{
	int n=5,flag=0;
	int mina,minie;
	int CT;
	int temp;
	for(int i=0; i<5; i++)
	{
		cout<<"Enter the process ID:\t";
		cin>>pid[i];
		cout<<"Enter the arrival time:\t";
		cin>>arrival_Time[i];
		cout<<"Enter the Burst time:\t";
		cin>>burst_Time[i];
		//duplicate_Burst_Time[i]=burst_Time[i];
	}

	for(int i=0; i<n; i++)
	{
		check[i]=0;
	}

	cout<<"PID  Arrival Time   Burst Time  Completion Time  Turn Around Time  Waiting Time \n";
	for (int i = 0; i < n; i++)
	{
		minie=minimum_arrival();
		mina=minimum_burst();
		if(check[i]==0 && arrival_Time[i]==minie)
		{
			completion_Time[i]=arrival_Time[i]+burst_Time[i];
			check[i]=1;
		}
		else if(check[i]==0 && burst_Time[i]==mina)
		{
			completion_Time[i]=CT+burst_Time[i];
			check[i]=1;
		}
		CT=completion_Time[i];
		turn_Around_Time[i]=completion_Time[i]-arrival_Time[i];
		waiting_Time[i]=turn_Around_Time[i]-burst_Time[i];
		cout<<pid[i]<<"\t "<<arrival_Time[i]<<" \t\t"<<burst_Time[i]<<" \t\t"<<completion_Time[i]<<" \t\t"<<turn_Around_Time[i]<<" \t\t"<<waiting_Time[i]<<"\n";
	}
}