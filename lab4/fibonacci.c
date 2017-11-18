#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
   int a=0, b=1, n=a+b,i,k;
   pid_t pid;

   printf("Enter the Sequence size:\n");
   scanf("%d", &k);

   if (k < 0)
      printf("Please enter a non-negative integer!\n");
   else
   {
      pid = fork();
      if (pid == 0)
      {
         printf("Child is producing the Fibonacci Sequence...\n");
         printf("%d %d",a,b);
         for (i=0;i<k;i++)
         {
            n=a+b;
            printf(" %d", n);
            a=b;
            b=n;
         }
         printf("\nChild ends\n");
      }
     /* else 
      {
         printf("Parent is waiting for child to complete...\n");
         wait(0);
         printf("Parent ends\n");
      }*/
      else
      {
         wait(0);
         int j = 3, count=2, c;
     
       /*printf("Enter the number of prime numbers required\n");
       scanf("%d",&k);*/
         printf("Parent is producing the Prime number Sequence...\n");
         if ( k >= 1 )
         {
            printf("First %d prime numbers are :\n",k);
            printf("2\n");
         }
       
         while(count<=k)
         {
            for ( c = 2 ; c <= j - 1 ; c++ )
            {
               if ( j%c == 0 )
               break;
            }
            if ( c == j )
            {
               printf("%d\n",j);
               count++;
            }
            j++;
         }         
      }
   }
      return(0);
   }
