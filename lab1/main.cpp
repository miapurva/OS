#include <iostream>
#include "fcfs.h"
using namespace std;

int main(void)
{
	int temp;
	for(int i=0; i< n; i++)
	{
		cout<<"Enter the process ID:\t";
		cin>>pid[i];
		cout<<"Enter the arrival time:\t";
		cin>>arrival_Time[i];
		duplicate_Arrival_Time[i]=arrival_Time[i];
		cout<<"Enter the Burst time:\t";
		cin>>burst_Time[i];
	}

	for(int i=0; i<n; i++)
	{
		for(int j=0;j<n-i-1 ;j++)
		{
			if(duplicate_Arrival_Time[i]>duplicate_Arrival_Time[j])
			{
				temp=duplicate_Arrival_Time[j];
				duplicate_Arrival_Time[j]=duplicate_Arrival_Time[j+1];
				duplicate_Arrival_Time[j+1]=temp;
			}
		}
	}

	void fcfs();

}