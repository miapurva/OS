#include "fcfs_sjf.h"
#include <iostream>
using namespace std;


int fcfs_sjf_h::minimum()
{
	int minie=arrival_Time[0];
	for(int i=0;i<5;i++)
	{
		if(arrival_Time[i]<minie)
			minie=arrival_Time[i];
	}
	return (minie);
}

void fcfs_sjf_h::sjf()
{
	int n=5,flag=0;
	int min,minie;
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
		duplicate_Burst_Time[i]=burst_Time[i];
	}
	for(int i=0; i<5; i++)
	{
		for(int j=0;j<5-i-1 ;j++)
		{
			if(duplicate_Burst_Time[j]>duplicate_Burst_Time[j+1])
			{
				temp=duplicate_Burst_Time[j];
				duplicate_Burst_Time[j]=duplicate_Burst_Time[j+1];
				duplicate_Burst_Time[j+1]=temp;
			}
		}
	}
	//calculation
	cout<<"PID  Arrival Time   Burst Time  Completion Time  Turn Around Time  Waiting Time \n";
	for(int i=0; i<n; i++)
		{
				for (int j = 0; j < n; j++)
				{
					if(duplicate_Burst_Time[i]==burst_Time[j])
						min=j;
				}
				minie=minimum();
				//cout<<"Minimum"<<minie<<"\n";
						//CT=completion_Time[min];
					if(arrival_Time[i]==minie)
					{
						completion_Time[i]=arrival_Time[i]+burst_Time[i];
						flag=1;
					}
					if(flag!=1)
					{
						completion_Time[min]=CT+burst_Time[min];
						flag=0;
						
					}
						
						CT=completion_Time[min];
						turn_Around_Time[min]=completion_Time[min]-arrival_Time[min];
						waiting_Time[min]=turn_Around_Time[min]-burst_Time[min];
						//print
						
						cout<<pid[min]<<"\t "<<arrival_Time[min]<<" \t\t"<<burst_Time[min]<<" \t\t"<<completion_Time[min]<<" \t\t"<<turn_Around_Time[min]<<" \t\t"<<waiting_Time[min]<<"\n";
					
		}
		/*for (int k = 0; k < 5; k++)
		{
			cout<<"\n"<<duplicate_Burst_Time[k]<<" ";
		}*/
}

