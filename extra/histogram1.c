#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int main(void)
{
	char str[15];
	printf("Give an input string:\n");
	gets(str);
	int len=strlen(str);
	int l;
	l=0;
	int flag=0;
	char dupStr[len];
	int p;
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j <=l; ++j)
		{
			if(dupStr[j]!=str[i])
			{
				count[l]=1;
				flag=1;
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
	/*for (int i = 0; i < len; ++i)
	{
		printf(" %c\n",dupStr[i] );
	}
	*/
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