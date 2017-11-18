#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE1 3
#define SIZE2 3
#define SIZE3 3


int res[SIZE1][SIZE3];

typedef struct Subcal{

	int rowi;
	int rowj;    
	int row1[SIZE2];
	int row2[SIZE2];
	
} subcal;


void *mul(void* r){
	
	int i,j,sum = 0;
	
	subcal *d = (subcal *)r;
	
	for(i=0;i<SIZE2;i++){
		sum += d->row1[i] * d->row2[i];
	}
	
	
//	printf(" %d %d -> %d \n",d->rowi , d->rowj,sum);
		
	res[d->rowi][d->rowj] = sum;	
	
	pthread_exit(0);
}


int main(){
    
	pthread_attr_t tattr;
    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_OTHER);
    
    pthread_t t[SIZE1];
    
    int a[SIZE1][SIZE2]={{1,2,3},
    			 {1,2,3},
    			 {1,2,3}
    			};

    int b[SIZE2][SIZE3]={{1,2,3},
    			 {1,2,3},
    			 {1,2,3}
    			};


    subcal result[SIZE1][SIZE3];

    int i,j,k;
    for(i = 0 ; i<SIZE1 ; i++){
    
	for( j=0 ; j<SIZE3 ; j++)
	{
	  
	  for( k=0 ; k<SIZE2 ; k++){
	  	result[i][j].rowi = i;
	  	result[i][j].rowj = j;
	  	result[i][j].row1[k] = a[i][k];
	  	result[i][j].row2[k] = b[k][j];
	  }
	  
	  pthread_create(&t[i] , &tattr , mul ,&result[i][j]); 
	} 
	
    
    }


    for(i = 0 ; i<SIZE1 ; i++){

	 pthread_join(t[i], NULL );
    
    }
	
	printf("\nInput 1: \n");
	for(i=0 ; i<SIZE1 ; i++){
	
		for( j=0 ; j<SIZE3; j++){
			
			printf(" %d ",a[i][j]);
		
		}
		
		printf("\n");	
	}

	printf("\nInput 2: \n");
	for( i=0 ; i<SIZE1 ; i++){
	
		for( j=0 ; j<SIZE3; j++){
			
			printf(" %d ",b[i][j]);
		
		}
		
		printf("\n");	
	}
		
	printf("\nResult: \n");
	for( i=0 ; i<SIZE1 ; i++){
	
		for( j=0 ; j<SIZE3; j++){
			
			printf(" %d ",res[i][j]);
		
		}
		
		printf("\n");	
	} 		
 	   
	return 0;

}