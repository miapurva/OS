#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 3
#define N 3
#define NUM_THREADS 10

int A [M][K] = { {1,1,1}, {1,1,1}, {1,1,1} };
int B [K][N] = { {1,1,1}, {1,1,1}, {1,1,1} };
int C [M][N];

struct v {
   int i; /* row */
   int j; /* column */
};

void *runner(void *param); /* the thread */

int main(int argc, char *argv[]) {

   int i,j, count = 0;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         //Assign a row and column for each thread
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /*Create the thread passing it data as a parameter */
         pthread_t tid;       
         pthread_attr_t attr; 
         pthread_attr_init(&attr);
         pthread_create(&tid,&attr,runner,data);
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         count++;
      }
   }

   //Print out the resulting matrix
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}

void *runner(void *param) {
   struct v *data = param; // the structure that holds our data
   int sum = 0; //the counter and sum

   //Row multiplied by column
   for(int n = 0; n< K; n++)
   {
      sum += A[data->i][n] * B[n][data->j];
   }
   C[data->i][data->j] = sum;
   //Exit the thread
   pthread_exit(0);
}