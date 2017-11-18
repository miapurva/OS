#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

void palindrome(char original[])
{
	int l=strlen(original);
	char rev[l];
	
	for (int i=0 ; i<l ; i++)
	{
		//printf("%c\n",original[i]);
		rev[i]=original[l-i-1];
		//k++;
	}
	//rev[k]='\0';
	printf("%s\n", rev);
	if(strcmp(rev,original)==0)
		printf("It is a palindrome\n");
	else
		printf("It is not a palindrome\n");
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
		printf("Sent Message: %s \n", write_string);
		write(fd[1],write_string,sizeof(write_string));
		exit(0);
	}
	else if(pid>0)
	{
		wait(NULL);
		close(fd[1]);
		message=read(fd[0],read_buffer, sizeof(read_buffer));
		palindrome(read_buffer);
		printf("Received Message: %s \n", read_buffer);	
			
				
	}
	return(0);
}