#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sign=1, i, j;

struct matrix
{
	int M[5][5];
	int size;
}A, Adjacent, Inv;

struct matrix input(struct matrix A)
{
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &A.size);
	printf("\nEnter the elements: \n");
	for (int i = 0; i < A.size; ++i)
		for (int j = 0; j < A.size; ++j)
			scanf("%d", &A.M[i][j]);
	return A;
}

void display(struct matrix A)
{
	for (int i = 0; i < A.size; ++i)
	{
		for (int j = 0; j < A.size; ++j)
			printf("%d \t", A.M[i][j]);
		printf("\n");
	}
}

struct matrix submat(struct matrix A, int r, int c)
{
	struct matrix B;
	B.size = A.size-1;

	int r1=0, c1=0;
	for (int i = 0; i < A.size; ++i)
		for (int j = 0; j < A.size; ++j)
			if (i!=r && j!=c)
			{
				B.M[r1][c1++]=A.M[i][j];
				// Row is filled, so increase row index and reset col index
				if (c1==B.size)
				{
					r1++;
					c1=0;
				}
			}
	return B;
}

int Determinant(struct matrix A)
{
	if (A.size==2)
		return A.M[0][0]*A.M[1][1]-A.M[0][1]*A.M[1][0];
	else
	{
		int det=0;
		for (int i = 0; i < A.size; ++i)
		{
				det += sign*A.M[0][i]*Determinant(submat(A, 0, i));
				sign = -1*sign;
		}
		return det;
	}
}

void* Cofactor()
{
	Adjacent.M[i][j] = sign*Determinant(submat(A, i, j));
	sign = -1*sign;
	
	if (j == Adjacent.size-1)
	{
		i++;
		j = 0;
	}
	else
		j++;

	pthread_exit(NULL);
}

struct matrix Inverse(struct matrix A, int det, struct matrix Adjacent)
{
	struct matrix D;
	D.size=A.size;
	int a=1/det;
	for (int i = 0; i < D.size; ++i)
		for (int j = 0; j < D.size; ++j)
			D.M[i][j]=a*Adjacent.M[i][j];
	return D;
}

int main()
{
	int det;
	A = input(A);
	printf("\nGiven matrix:\n");
	display(A);

	sign = 1;
	det = Determinant(A);
	printf("\nDeterminant of the matrix: %d\n", det);
	
	Adjacent.size = A.size;
	sign = 1;
	i = 0;
	j = 0;
	pthread_t t[Adjacent.size*Adjacent.size];
	
	printf("\nCofactor matrix:\n");

	for (int i = 0; i < Adjacent.size*Adjacent.size; ++i)
		pthread_create(&t[i], NULL, Cofactor, NULL);
	
	for (int i = 0; i < Adjacent.size*Adjacent.size; ++i)
		pthread_join(t[i], NULL);

	display(Adjacent);

	printf("\nAdjugate Matrix:\n");
	
	for (int i = 0; i < Adjacent.size; ++i)
		for (int j = 0; j < Adjacent.size; ++j)
			if(i<j)
			{
				int temp = Adjacent.M[i][j];
				Adjacent.M[i][j] = Adjacent.M[j][i];
				Adjacent.M[j][i] = temp;
			}
	
	display(Adjacent);

	printf("\nInverse of the matrix:\n");
	Inv = Inverse(A, det, Adjacent);
	display(Inv);
	printf("\n");
	
	return 0;
}