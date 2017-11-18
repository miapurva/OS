#include "prioritynpe_h.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void priority_npe_h::priority_npe()
{
	srand(time(NULL));
	int n=5, CT=0, index=0,flag=0;
	//cout<<"Enter the number of processes:\t ";
	//n=rand()%7;
	for(int i=0; i<5; i++)
	{
		/*cout<<"Enter the process ID:\t";
		cin>>pid[i];
		cout<<"Enter the arrival time:\t";
		cin>>arrival_Time[i];
		cout<<"Enter the Burst time:\t";
		cin>>burst_Time[i];*/
		pid[i]=i+1;
		arrival_Time[i]=rand()%10;
		burst_Time[i]=(rand()%10)+1;
		priority_Array[i]=(rand()%10)+1;
		//duplicate_Burst_Time[i]=burst_Time[i];
	}
	/*for (int i = 0; i <  n; ++i)
	{
		cout<<arrival_Time[i]<<" "<<burst_Time[i]<<endl;
	}*/
	for(int i=0; i < n-1; i++)
	{
		int temp;
		for(int j=0; j < n-i-1; j++)
		{
			if(arrival_Time[j]>arrival_Time[j+1])
			{
				temp=arrival_Time[j];
				arrival_Time[j]=arrival_Time[j+1];
				arrival_Time[j+1]=temp;

				temp=burst_Time[j];
				burst_Time[j]=burst_Time[j+1];
				burst_Time[j+1]=temp;

				temp=priority_Array[j];
				priority_Array[j]=priority_Array[j+1];
				priority_Array[j+1]=temp;

				temp=pid[j];
				pid[j]=pid[j+1];
				pid[j+1]=temp;
			}
		}
	}
	for (int i = 0; i <  n; ++i)
	{
		cout<<arrival_Time[i]<<" "<<burst_Time[i]<<" "<<priority_Array[i]<<endl;
	}

	for(int i=0; i<n; i++)
	{
		check[i]=0;
	}
	int remain=0;
	cout<<"PID  Arrival Time   Burst Time  Priority Array  Completion Time  Turn Around Time  Waiting Time \n";
	for (int time = 0; remain!=n; time++)
	{
		int max=0;
		cout<<"max";
		for(int j=0;j<n;j++)
		{
			if((j==0) && (check[j]==0))
			{
				index=j;
				completion_Time[index] = arrival_Time[0] + burst_Time[0];
				CT=completion_Time[index];
				//turn_Around_Time[index] = completion_Time[index] - arrival_Time[index];
				//waiting_Time[index]=turn_Around_Time[index]-burst_Time[index];
				remain++;
				//check[index]=1;					
			}
			else if((j!=0) && (check[j]==0) && (priority_Array[j] > max) && (arrival_Time[j]<=CT))
			{
				//flag=1;
				index=j;
				max = priority_Array[j];
			}
			else if((flag==0)&&(arrival_Time[index]>CT)&&(index!=0))
			{
				CT= time+1;
				break;
			}
		}
		/*if((flag==0)&&(arrival_Time[index]>CT)&&(index!=0))
		{
			//continue;
			CT=time+1;
		}*/
		check[index]=1;
       // cout<<"prio"<<index<<endl;
		/*cout<<"check"<<endl;
			for(int k=0;k<n;k++)
			{
				cout<<check[k]<<endl;
			}*/
		if(arrival_Time[index]<=CT && index>0)
		{
			//cout<<"Index "<< index<<endl;
			completion_Time[index] = CT + burst_Time[index];
			remain++;
			CT=completion_Time[index];
			turn_Around_Time[index] = completion_Time[index] - arrival_Time[index];
			waiting_Time[index]=turn_Around_Time[index]-burst_Time[index];
			//cout<<"Completion:2 "<<completion_Time[index]<<endl;
		}
		//cout<<pid[index]<<"\t "<<arrival_Time[index]<<" \t\t"<<burst_Time[index]<<" \t\t"<<priority_Array[index]<<" \t\t"<<completion_Time[index]<<" \t\t"<<turn_Around_Time[index]<<" \t\t"<<waiting_Time[index]<<"\n";
	}
	for (int i = 0; i < n; ++i)
	{
		cout<<"\t\t\t"<<pid[i]<<"\t "<<arrival_Time[i]<<" \t\t"<<burst_Time[i]<<" \t\t"<<priority_Array[i]<<" \t\t"<<completion_Time[i]<<"\n";
	}
}
