#include <stdio.h>
 
void main()
    {
       int k, j = 3, count=2, c;
     
       printf("Enter the number of prime numbers required\n");
       scanf("%d",&k);
     
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
      // return 0;
     

