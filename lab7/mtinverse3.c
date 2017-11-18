#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sign=1,g,h;

struct matrix
{
	float M[5][5];
	int size;
}A, Adj, Inv;

/*
struct matrix input(struct matrix A)
{
	printf("\nEnter the size of the matrix: ");
	scanf("%d", &A.size);
	printf("\nEnter the elements: \n");
	for (int i = 0; i < A.size; ++i)
		for (int j = 0; j < A.size; ++j)
			scanf("%f", &A.M[i][j]);
	return A;
}*/

void display(struct matrix A)
{
	for (int i = 0; i < A.size; ++i)
	{
		for (int j = 0; j < A.size; ++j)
			printf("%f\t", A.M[i][j]);
		printf("\n");
	}
}

struct matrix MiniMatrix(struct matrix A, int r, int c)
{
	struct matrix B;
	B.size = A.size-1;

	int r1=0, c1=0;
	for (int i = 0; i < A.size; ++i)
		for (int j = 0; j < A.size; ++j)
			if (i!=r && j!=c)
			{
				B.M[r1][c1++]=A.M[i][j];
				if (c1==B.size)
				{
					r1++;
					c1=0;
				}
			}
	return B;
}

float Determinant(struct matrix A)
{
	if (A.size==2)
		return A.M[0][0]*A.M[1][1]-A.M[0][1]*A.M[1][0];
	else
	{
		float det=0;
		for (int i = 0; i < A.size; ++i)
		{
				det += sign*A.M[0][i]*Determinant(MiniMatrix(A, 0, i));
				sign = -1*sign;
		}
		return det;
	}
}

void* Cofactor()
{
	Adj.M[g][h] = sign*Determinant(MiniMatrix(A, g, h));
	sign = -1*sign;
	
	if (h == Adj.size-1)
	{
		g++;
		h = 0;
	}
	else
		h++;

	pthread_exit(NULL);
}

struct matrix Inverse(struct matrix A, float det, struct matrix Adj)
{
	struct matrix D;
	D.size=A.size;
	float onebydet=1/det;
	for (int i = 0; i < D.size; ++i)
		for (int j = 0; j < D.size; ++j)
			D.M[i][j]=onebydet*Adj.M[i][j];
	return D;
}

int main()
{
	float det;
	A.size=3;
	A.M[size][size]={{1, 0, 2, -1},
                     {3, 0, 0, 5},
                     {2, 1, 4, -3},
                     {1, 0, 5, 0}};
	A = input(A);
	printf("\nGiven matrix:\n");
	display(A);

	sign = 1;
	det = Determinant(A);
	printf("\nDeterminant of the matrix: %f\n", det);
	
	Adj.size = A.size;
	sign = 1;
	g = 0;
	h = 0;
	pthread_t th[Adj.size*Adj.size];
	
	printf("\nCofactor matrix:\n");

	for (int i = 0; i < Adj.size*Adj.size; ++i)
		pthread_create(&th[i], NULL, Cofactor, NULL);
	
	for (int i = 0; i < Adj.size*Adj.size; ++i)
		pthread_join(th[i], NULL);

	display(Adj);

	printf("\nAdjugate Matrix:\n");
	
	for (int i = 0; i < Adj.size; ++i)
		for (int j = 0; j < Adj.size; ++j)
			if(i<j)
			{
				int temp = Adj.M[i][j];
				Adj.M[i][j] = Adj.M[j][i];
				Adj.M[j][i] = temp;
			}
	
	display(Adj);

	printf("\nInverse of the matrix:\n");
	Inv = Inverse(A, det, Adj);
	display(Inv);
	printf("\n");
	
	return 0;
}