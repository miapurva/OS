#include <stdio.h>
#include <stdbool.h>
#define MAX 7

//int intArray[MAX] = {4,6,3,2,1,9,7};

void printline(int count) {
   int i;
	
   for(i = 0;i <count-1;i++) {
      printf("=");
   }
	
   printf("=\n");
}

void display(int intArray[]) {
   int i;
   printf("[");
	
   // navigate through all items 
   for(i = 0;i<MAX;i++) {
      printf("%d ",intArray[i]);
   }
	
   printf("]\n");
}

void swap(int num1, int num2, int intArray[]) 
{
   int temp = intArray[num1];
   intArray[num1] = intArray[num2];
   intArray[num2] = temp;
}

int partition(int left, int right, int pivot,int intArray[])
{
   int leftPointer = left -1;
   int rightPointer = right;

   while(true) 
   {
      while(intArray[++leftPointer] < pivot) 
      {
         //do nothing
      }
		
      while(rightPointer > 0 && intArray[--rightPointer] > pivot) 
      {
         //do nothing
      }

      if(leftPointer >= rightPointer) 
      {
         break;
      } 
      else 
      {
         printf(" item swapped :%d,%d\n", intArray[leftPointer],intArray[rightPointer]);
         swap(leftPointer,rightPointer,intArray);
      }
   }
	
   printf(" pivot swapped :%d,%d\n", intArray[leftPointer],intArray[right]);
   swap(leftPointer,right,intArray);
   printf("Updated Array: "); 
   display(intArray);
   return leftPointer;
}

void quickSort(int left, int right, int intArray[]) {
   if(right-left <= 0) {
      return;   
   } else {
      int pivot = intArray[right];
      int partitionPoint = partition(left, right, pivot,intArray);
      quickSort(left,partitionPoint-1,intArray);
      quickSort(partitionPoint+1,right,intArray);
   }        
}

int main(void) 
{
   printf("Input Array: ");
   int Array[MAX];
   for (int i = 0; i < MAX; ++i)
   {
      scanf("%d", &Array[i]);
   }
   display(Array);
   printline(50);
   quickSort(0,MAX-1,Array);
   printf("Output Array: ");
   display(Array);
   printline(50);
   return(0);
}