#include "myscheduler.h"

#include <iostream>
#include <cstdlib>
//#include<queue>
using namespace std;

# define SIZE 100
class queue
{
              int queue1[SIZE];
              int rear,front;
      public:
              queue()
                {
                     rear=-1;
                     front=-1;
                }
              void insert(int x)
               {
                   if(rear >=  SIZE - 1)
                    {
                       cout <<"queue over flow";
                       return;
                    }
                    queue1[++rear]=x;
                    //display();
                    //cout <<"inserted" <<x;
               }
              void del()
               {
                   if(front==rear)
                     {
                         cout <<"queue under flow";
                         return;
                     }
                     front = front + 1;
                     //display();
                     //cout <<" deleted"<<queue1[++front];
                }
              int fr()
              {
                   if(rear==front)
                     {
                          cout <<" queue empty";
                          return -1;
                     }
                   return queue1[front+1];
                   //cout<<"\nRear element is: "<<queue1[rear]<<" ";
              }
              void display()
               {
                   if(rear==front)
                     {
                          cout <<" queue empty";
                          return;
                     }
                   for(int i=front+1;i<=rear;i++)
                   cout <<queue1[i]<<" ";
               }
};

void MyScheduler :: Rrobin(int m)
{

   queue q ;    // Ready Queue

   int TS;
   cout<<"Enter Time Quantum/Slice : ";
   cin>>TS;

   fcfs(m);
   int RT[n];            // Remaining Time
   int flag[n];           // To indicate if the element was pushed into queue atleast once
   for(int i=0;i<n;i++)
   {
      RT[i] = BT[i] ;
      flag[i] = 0;
   }

   int at = AT[0],c;
   for(int i=0;i < n ;i++)
   {
      if(AT[i] == AT[0])
      {
        q.insert(i);
        cout<<"\n"<<pid[i]<<" is pushed";
        flag[i] = 1;
      }
   }
   int popped = -1;
   int f = q.fr();
   q.del();
  int y=0;
   if(RT[0] <= TS)
   {
     c = AT[0] + RT[0] ;
     CT[0] = c;
     RT[0] = 0;
     cout<<"\n"<<pid[f]<<" is completed";
     y = 1;
   }
   else
   {
      popped =f;
      cout<<"\n"<<pid[0]<<" is popped";
      c = AT[0] + TS;
      RT[0] = RT[0] - TS;
   }

   while(y<n)
   {
      cout<<"\nFirst Ready queue: ";
      q.display();
      cout<<endl;
      for(int i=0;i<n;i++)
      {
         if(AT[i] <= c  && flag[i] == 0)
         {
            q.insert(i);
            cout<<"\n"<<pid[i]<<" is pushed";
            cout<<"\nReady queue: ";
            q.display();
            cout<<endl;
            flag[i] = 1;
         }
      }
      if(popped != -1)
      {
         cout<<"\n"<<pid[popped]<<" is pushed";
         q.insert(popped);
         cout<<"\nReady queue: ";
         q.display();
         cout<<endl;
      }
      int f = q.fr();
      cout<<"\n"<<f<<":  "<<pid[f]<<" is in front of queue";
      cout<<"\nReady queue: ";
      q.display();
      cout<<endl;
      at = c;
      if(RT[f] <= TS)
      {
         q.del();
         cout<<"\n"<<pid[f]<<" is completed";
         y = y+1;
         cout<<"\nReady queue: ";
         q.display();
         cout<<endl;
         CT[f] = at + RT[f];
         RT[f] = 0;
         popped = -1;
         c = CT[f];
      }
      else
      {
         popped = f;
         q.del();
         cout<<"\n"<<pid[f]<<" is popped";
         cout<<"\nReady queue: ";
         q.display();
         cout<<endl;
         RT[f] = RT[f] - TS;
         cout<<"f : "<<f<<" and RT : "<<RT[f];
         c = at + TS;
      }
   }
   if(m == 5)
   {
     calTAT();
     calWT();
     cout<<"\n....................................."<<endl;
     cout<<"\nAfter Scheduling"<<endl;
     print(m);
   }
}