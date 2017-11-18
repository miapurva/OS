#include "fcfs_sjf.h"
#include <iostream>
using namespace std;

void fcfs_sjf_h::fcfs()
{
	int n=5;
	int min, CT;
	int temp;
	float sum_wait=0;
	for(int i=0; i<5; i++)
	{
		cout<<"Enter the process ID:\t";
		cin>>pid[i];
		cout<<"Enter the arrival time:\t";
		cin>>arrival_Time[i];
		duplicate_Arrival_Time[i]=arrival_Time[i];
		cout<<"Enter the Burst time:\t";
		cin>>burst_Time[i];
	}

	for(int i=0; i<5; i++)
	{
		for(int j=0;j<5-i-1 ;j++)
		{
			if(duplicate_Arrival_Time[j]>duplicate_Arrival_Time[j+1])
			{
				temp=duplicate_Arrival_Time[j];
				duplicate_Arrival_Time[j]=duplicate_Arrival_Time[j+1];
				duplicate_Arrival_Time[j+1]=temp;
			}
		}
	}
	cout<<"PID  Arrival Time   Burst Time Completion Time  Turn Around Time  Waiting Time \n";
	for(int i=0; i<n; i++)
		{
				for (int j = 0; j < n; j++)
				{
					if(duplicate_Arrival_Time[i]==arrival_Time[j])
						min=j;
				}
					if(i==0)
					{
						completion_Time[min]=arrival_Time[min]+burst_Time[min];
					}
					else
					{
						completion_Time[min]=CT+burst_Time[min];
						
					}
						
						CT=completion_Time[min];
						
						turn_Around_Time[min]=completion_Time[min]-arrival_Time[min];
						waiting_Time[min]=turn_Around_Time[min]-burst_Time[min];
						sum_wait+=waiting_Time[min];
						cout<<pid[min]<<"\t "<<arrival_Time[min]<<" \t\t"<<burst_Time[min]<<" \t\t"<<completion_Time[min]<<" \t\t"<<turn_Around_Time[min]<<" \t\t"<<waiting_Time[min]<<"\n";
					
		}
		cout<<"\nAverage waiting time:\t"<<(sum_wait/n)<<endl;
}





