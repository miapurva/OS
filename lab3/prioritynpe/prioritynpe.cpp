#include "prioritynpe_h.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void priority_npe_h::priority_npe()
{
	srand(time(NULL));
	int n;
	float sum_wait=0;
	int index=0,index1,temp;
	//priorityarray[9]=-999;
	cout<<"Enter the number of processes:\n";
	cin>>n;
	for(int i=0; i<n; i++)
	{
		//pid[i]=i+1;
		//cout<<"Enter the arrival time:\t";
		arrival_Time[i]=rand()%10;
		//cin>>arrival_Time[i];
		//cout<<"Enter the Burst time:\t";
		//cin>>burst_Time[i];
		burst_Time[i]=(rand()%10) + 1;
		//cout<<"Enter the priority:\t";
		priority_Array[i]=(rand()%10)+1;
		//cin>>priority_Array[i];
		//arrival_Time[i]=rand()%15;
		//priority_Array[i]=rand()%15+1;
		//burst_Time[i]=(rand()%15)+1;
	}

	/*for(int k=0;k<n;k++)
	{
		cout<<arrival_Time[k]<<"   "<<burst_Time[k]<<endl;
	}*/


	for(int i=0; i<n; i++)
	{
		check[i]=0;
	}

	for(int i = 0; i < n-1; i++)
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

				temp=priority_Array[j];
				priority_Array[j]=priority_Array[j+1];
				priority_Array[j+1]=temp;

				/*temp=remaining_Time[j];
				remaining_Time[j]=remaining_Time[j+1];
				remaining_Time[j+1]=temp;*/

				/*temp=pid[j];
				pid[j]=pid[j+1];
				pid[j+1]=temp;*/
			}
		}
	}

  
     int j;
	int remain=0,CT,flag=0;
	int end_time=0;
	cout<<"PID  Arrival Time \tBurst Time \tPriority \tCompletion Time \tTurn Around Time \tWaiting Time \n";
	for (int i = 0; i < n; i++)
	{
		//priority_Array[index]=0;	
		//for the first process
		int max=0;
		
		if(i==0 && check[i]==0)
		{
			completion_Time[index] = arrival_Time[i] + burst_Time[i];
			//index=index+1;
			check[i]=1;
		}
		else if(check[i]==0 && i!=0)
		{
			for( j = 1; j < n; j++)//max priority
			{
				if(priority_Array[j]>max  && arrival_Time[j]<=completion_Time[index])
					//if(priority_Array[j]>max)
				{

					max=priority_Array[j];
					//index1=j;
                    index=j;
					cout<<"max priority "<<index<<" "<<priority_Array[index]<<endl;
				}
			}	
			check[index]=1;
			//index=index1;
			completion_Time[index]= CT + burst_Time[index];
			//completion_Time[index] = CT+burst_Time[index];
			cout<<"comple"<<completion_Time[index]<<endl;
		}
		
		CT = completion_Time[index];
		turn_Around_Time[index] = completion_Time[index]-arrival_Time[index];
		waiting_Time[index]=turn_Around_Time[index]-burst_Time[index];
		cout<<i+1<<"\t "<<arrival_Time[i]<<" \t\t"<<burst_Time[i]<<" \t\t"<<priority_Array[i]<<" \t\t"<<completion_Time[index]<<" \t\t\t"<<turn_Around_Time[index]<<" \t\t\t"<<waiting_Time[index]<<"\n";
		
	}

	/*for(int i=0;i<n;i++)
	{
		cout<<pid[i]<<"\t "<<arrival_Time[i]<<" \t\t"<<burst_Time[i]<<" \t\t"<<priority_Array[i]<<" \t\t"<<completion_Time[i]<<" \t\t\t"<<turn_Around_Time[i]<<" \t\t\t"<<waiting_Time[i]<<"\n";
		sum_wait+=waiting_Time[index];
	}
	
	sum_wait=sum_wait/n;
	cout<<"\n Average Waiting Time:\t"<<sum_wait<<endl;
	*/
}