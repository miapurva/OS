#include <stdio.h>
#include <stdlib.h>

void merge(int array[],int p, int q, int r)
{
	int n1=q-p+1;
	int n2=r-q;

	int L[n1],R[n2];

	for (int i = 0; i < n1; ++i)
	{
		L[i]=array[p+i-1];
	}
	for (int j = 0; j < n2; ++j)
	{
		R[j]=array[q+j];
	}
	L[n1+1]=R[n2+1]=3333;
	int i=1;
	int j=1;
	for (int k=p; k < r; k++)
	{
		if(L[i]<=R[j])
		{
			array[k]=L[i];
			i++;
		}
		else if(array[k]=R[j])
		{
			j++;
		}
	}
}

void mergesort(int array[],int p,int r)
{
	if(p<r)
	{
		int q=(p+r)/2;
		mergesort(array,p,q);
		mergesort(array,q+1,r);
		merge(array,p,q,r);
	}
}
/*
void display(int array[])
{
	
}
*/
int main(void)
{
	int Array[]={1,6,2,8,54,1,89};
	mergesort(Array,1,7);
	//display(Array);

	return(0);
}