#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int nos[10],n;
void ascending();
void descending();

int main(void)
{
  int pid;
  int i,j;
  printf("\nEnter the no of nos::");
  scanf("%d",&n);
  printf("\nEnter the Nos:");
  for(i=0;i<n;i++)
      scanf("%d",&nos[i]);
  pid=fork();
  if(pid==0)
  {
    printf("\nChild Process is Executing");
    printf("\nProcess ID = %d\nParent ID = %d",getpid(),getppid());
    ascending();
    printf("\n\n");
   }
   else
   {
    printf("\nParent Process is Executing");
    printf("\nProcess ID= %d\nParent ID= %d",getpid(),getppid());
    descending();
    printf("\n\n");
    }  

    return 0;
}

void ascending()
{
  int i,j,k,temp;
  for(i=0;i<n;i++)
  {
    for(j=i+1;j<n;j++)
    {
        if(nos[i]>nos[j])
        {
            temp=nos[i];
            nos[i]=nos[j];
            nos[j]=temp;  
        }
    }
   }

     printf("\n\nThe no in Ascending order are::\n");
         for(i=0;i<n;i++)
                printf("%d\t",nos[i]);

}

void descending()
{
  int i,j,k,temp;
  for(i=0;i<n;i++)
  {
        for(j=i+1;j<n;j++)
        {
                if(nos[i]<nos[j])
                {
                        temp=nos[i];
                        nos[i]=nos[j];
                        nos[j]=temp;
                }
        }
   }

    printf("\n\nThe no in Descending order are::\n");
        for(i=0;i<n;i++)
            printf("%d\t",nos[i]);
}