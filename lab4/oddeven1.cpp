#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>
#include "header.h"
using namespace std;

void oddeven:: odd_even()
{
	int n=20;
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		cout<<"Even series:\n";
		for (int i = 0; i < n; i++)
		{
			if(i%2==0)
			{
				cout<<" "<<i;
				
			}
			//sleep(0.001);
		}
		cout<<endl;
	}
	else
	{
		cout<<"Odd Series:\n";
		for (int i = 1; i < n; i++)
		{	if(i%2!=0)
			{
				cout<<" "<<i;
				
			}
			//sleep(0.001);
		}	
		cout<<endl;
		
	}
}
/*
void oddeven:: odd_even()
{
	pid_t pid;
	pid=fork();
	int n=20;
	for (int i = 0; i < n; ++i)
	{
		if(pid==0)
		{
				cout<<i<<"a " ;
				pid=1;
		}
		else{
				cout<<i<<"b " ;
				pid=0;
		}
	}
		
	
}*/