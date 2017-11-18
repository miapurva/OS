#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


void* inv()
{
	system("./mi_t");
	pthread_exit(0);
}
void* m()
{
	system("./mm_t");
	pthread_exit(0);
}
void* q()
{
	system("./qs_t");
	pthread_exit(0);
}

int main(){
	
	pthread_attr_t tattr;
    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_OTHER);
    pthread_t t[3];

    int  i;
    
    pthread_create(&t[0] , &tattr , inv , NULL);
    pthread_create(&t[1] , &tattr , m , NULL);
    pthread_create(&t[2] , &tattr , q , NULL);
    for ( i = 0; i < 3; ++i)
    {
    	pthread_join(t[i] , NULL);
    }
    	
    return 0;
}