#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define SIZE 3

int square[SIZE][SIZE];
int sum;

void *generateSquare(void * p)
{
    int n = *(int*)p;
    int magic[n][n]; 
    
    memset(magic, 0, sizeof(magic));
    
    int i = n/2;
    int j = n-1;
 
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n)
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
        if (magic[i][j])         
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magic[i][j] = num++;
 
        j++; i--;
    }
 
    
    printf("The Magic Square for n=%d:\nSum of each row or column %d:\n\n",n, n*(n*n+1)/2);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++){
            printf("%3d ", magic[i][j]);
            square[i][j] = magic[i][j];
        }
        printf("\n");
    }

    pthread_exit(0);
}

void* rowCheck(void* p){

    int index = *(int*)p;

    int i,check = 0;

    for (i = 0; i < SIZE; ++i)
    {
        check += square[i][index];
    }

    if (check == sum)
    {
        printf("Verifed Row %d \n", index);
    }

    pthread_exit(0);
}

void* colCheck(void* p){

    int index = *(int*)p;
    int i,check = 0;
    for (i = 0; i < SIZE; ++i)
    {
        check += square[index][i];
    }
    if (check == sum)
    {
        printf("Verifed Column %d \n", index);
    }
    pthread_exit(0);
}

void* diagCheck(void* p)
{
    int index = *(int*)p;
    int i,check = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        check += square[i][i];
    }
    if (check == sum)
    {
        printf("Verifed Diagonal %d \n", index);
    }
    pthread_exit(0);
}

int main()
{
    int n = SIZE; 
    
    sum = n*(n*n+1)/2;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
    pthread_t make_square;

    pthread_create(&make_square , &attr , generateSquare , &n);

    pthread_join(make_square,NULL);

  //int tcount = n + n + 2;

    pthread_t rowCheckThreads[n];
    pthread_t colCheckThreads[n];
    pthread_t diagCheckThreads[n];

    int v[n],h[n],m[n];

    for (int i = 0; i < n ; ++i)
    {
        v[i] = i;
        pthread_create(&rowCheckThreads[i] , &attr , rowCheck , &v[i]);
        pthread_join(rowCheckThreads[i] , NULL);
    }
    /*for (int i = 0; i < n; ++i)
    {
    }
*/
    for (int i = 0; i < n; ++i)
    {
        h[i] = i;
        pthread_create(&colCheckThreads[i] , &attr , colCheck , &h[i]);
        pthread_join(colCheckThreads[i] , NULL);

    }
    for (int i = 0; i < n; ++i)
    {
        m[i]=i;
        pthread_create(&diagCheckThreads[i], &attr, diagCheck, &m[i]);
        pthread_join(diagCheckThreads[i], NULL);
    }

    return 0;
}