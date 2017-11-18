#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

void palindrome(char original[])
{
	int l=strlen(original)-1;
	char rev[l];
	int k;
	k=0;
	int flag;
	for (int i = l; i >=0; i--)
	{
		printf("%c\n",original[i]);
		rev[k]=original[i];
		k++;
	}
	rev[k]='\0';
	printf("%s\n", rev);
	/*if(strcmp(rev,original)==0)
		printf("It is a palindrome\n");
	else
		printf("It is not a palindrome\n");*/
	for(int i=0;i<l;i++)
	{
		if(rev[i]!=original[i])
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		printf("not palin");
	else
		printf("yes" );
}

int main(void)
{
	int fd[2],message;
	pid_t pid;
	char write_string[100],read_buffer[100];

	printf("Enter the message\t:\n");
	gets(write_string);
	//printf("%s\n", write_string);
	pipe(fd);
	pid=fork();

	if(pid==-1)
	{
		perror("Fork unsuccessful\nTerminating unsuccessfully!\n");
		exit(1);
	}
	else if(pid==0)
	{
		close(fd[0]);
		//printf("SENDER:\n");
		printf("Sent Message: %s \n", write_string);
		//printf("\n");
		write(fd[1],write_string,sizeof(write_string));
		exit(0);
	}
	else if(pid>0)
	{
		wait(NULL);
		close(fd[1]);
		message=read(fd[0],read_buffer, sizeof(read_buffer));
		//printf("RECEIVER:\n");
		palindrome(read_buffer);
		printf("Received Message: %s \n", read_buffer);	
			
				
	}
	return(0);
}