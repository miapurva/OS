#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
// A function to generate odd sized magic squares
void generateSquare(int n)
{
    int magicSquare[n][n];

    memset(magicSquare, 0, sizeof(magicSquare));

    // Initialize position for 1
    int i = n/2;
    int j = n-1;

    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
            if (j == n)
                j = 0;
            if (i < 0)
                i=n-1;
        }
        if (magicSquare[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; //set number
 
        j++; i--; //1st condition
    }
 
   
}
 
// Driver program to test above function
int main()
{
    int n; // Works only when n is odd
    printf("Enter the order of matrix:\n");
    scanf("%d", &n);
    int magicSquare[n][n];

    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        // Print magic square
        printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",n, n*(n*n+1)/2);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                printf("%3d ", magicSquare[i][j]);
            printf("\n");
        }
    }
    else if(pid>0)
    {
        generateSquare (n);
    }
    return 0;
}