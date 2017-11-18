//withour sorting arrival time and condition missing for same burst time

#include "srt_h.h"
#include <iostream>
using namespace std;

void srt_h::srt()
{
	int n;
	//cout<<"\t\t\t\tWELCOME\n";
	cout<<"Enter the number of processes:\n";
	cin>>n;

	for(int i=0; i<n; i++)
	{
		/*cout<<"\nEnter the process ID:\t";
		cin>>pid[i];*/
		pid[i]=i+1;
		cout<<"\nEnter the arrival time:\t";
		cin>>arrival_Time[i];
		
		cout<<"Enter the Burst time:\t";
		cin>>burst_Time[i];
		remain_Time[i]=burst_Time[i];
	}
	//cout<<"PID  Arrival Time   Burst Time  Completion Time  Turn Around Time  Waiting Time \n";
	int remain=0,sum_wait=0, end_Time, smallest;
	cout<<"\n\nProcess Finish\t| Completion Time | Turnaround Time | Waiting Time\n\n";
	int process_f=0;

	for(int j=0;remain!=n;j++)
	{
		//cout<<"hi1\n";
		smallest=9;
		for (int k = 0; k < n; k++)
		{
		//	cout<<"hi2\n";
			if((arrival_Time[k]<=j) && (remain_Time[k]<remain_Time[smallest]) && (remain_Time[k]>0))
				smallest=k;
		}
		//calculating remaining time
		remain_Time[smallest]--;				//remaining_time=remaining_time-1
		if(remain_Time[smallest]==0)
		{
			process_finish[process_f]=smallest+1;
			process_f++;
			pid[smallest]=smallest+1;
			int turn_Around_Time;
			remain++;
			//calculation
			end_Time=j+1;
			turn_Around_Time=end_Time- arrival_Time[smallest];
			waiting_Time[smallest]=turn_Around_Time-burst_Time[smallest];
			//print
			cout<<"\n\tP["<<smallest+1<<"]\t|\t"<<end_Time<<"\t|\t"<<turn_Around_Time<<"\t|\t"<<waiting_Time[smallest];
			//for calculating average
			sum_wait+=turn_Around_Time -burst_Time[smallest];
		}
	}
	cout<<"\n\nAverage waiting time ="<<sum_wait*1.0/n;
}
