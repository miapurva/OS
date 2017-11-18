#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
char str[50];
char dupStr[50];
int l=0;
int count[50];

void *function(void *param)
{

	int len=*(int*)param;
	int flag=0;
	
	//pthread_t tid[l];
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j <=l; ++j)
		{
			if(dupStr[j]!=str[i])
			{
				count[l]=1;
				flag=1;
				/*pthread_create(&tid[i], &attr, NULL, NULL);
				pthread_join(&tid[i], NULL);
				*/
			}
			else if(dupStr[j]==str[i])
			{
				flag=-1;
				count[j]+=1;
				break;
			}
		}
		if(flag==1)
		{
			flag=0;
			dupStr[l]=str[i];
			l++;
		}
	}
	pthread_exit(0);
}

int main(void)
{
	
	printf("Give an input string:\n");
	gets(str);
	int len=strlen(str);
	//int count[len];
	//memset(count,0,strlen(str));
	char dupStr[len];
	
	pthread_t Histogram;
	pthread_attr_t attr;
    pthread_attr_init(&attr);
	pthread_create(&Histogram,&attr,&function,NULL);
    pthread_join(Histogram,NULL);
    
	
	//function(dupStr, len, count);

   //pthread_t tid[l];
	printf("%s%13s%17s\n","Element/index", "Value", "Histogram");
    for(int i=0; i <l; ++i)
    {
        printf("%9c%15d            ", dupStr[i],count[i]);
        for(int j = 1; j<= count[i]; j++)
            printf("*");
        printf("\n");
    }
	return(0);
}
