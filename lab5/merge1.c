#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void merge(int array[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1+ j];

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
    }
}
 
void printArray(int A[],int start, int size)
{
    int i;
    for (i=start; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main()
{
    //int array[] = {12, 11, 13, 5, 6, 7};
    //int array_size = sizeof(array)/sizeof(array[0]);
    int array_size;
    printf("Enter the array size\t:\n");
    scanf("%d", &array_size);

    int array[array_size];
    int l=array[0],r=array[array_size-1];

    printf("Enter the numbers\t:\n");
    for (int i = 0; i < array_size; ++i)
    {
        scanf("%d", &array[i]);
    }

    printf("Given array is\t:\n");
    printArray(array,0, array_size);
    int pivot=array_size/2;
   
    printf("Sorted array is:\n");
    pid_t pid;
    pid=fork();
    //int m = (l+(r-l))/2;
    if(pid==0)
    {
        mergeSort(array, 0, pivot);
        printArray(array,0, pivot+1);
        //printf("hiiii\n");    
    }
    else
    {
        wait(0);
        mergeSort(array, pivot+1,array_size-1);
        printArray(array,pivot+1, array_size); 
    }
    return 0;
}
