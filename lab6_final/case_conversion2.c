#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
/*
void upper_case(char string[], int c)
{
	c=0;
	if(string[c]>='a' && string[c]<='z')
	{
		string[c]=string[c]-32;
	}
}
/*
void lower_case(char string[])
{
	int c=0;
	while(string[c]!='\0')
	{
		if(string[c]>='A' && string[c]<='Z')
		{
			string[c]=string[c]+32;
		}
		c++;
	}
}
*/
int main(void)
{
	pid_t pid;
	int fd[2], message;
	char write_string[100];
	char read_buffer[100];

	//INPUT
	printf("Enter the message\t:\n");
	fgets(write_string,100,stdin);
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
		printf("SENDER:\n");
		printf("Sent Message: %s \n", write_string);
		printf("\n");
		write(fd[1],write_string,sizeof(write_string));
		exit(0);
	}
	else if(pid>0)
	{
		wait(NULL);
		close(fd[1]);
		message=read(fd[0],read_buffer, sizeof(read_buffer));
		int c=0;
		while(read_buffer[c]!='\0')
		{
			if(read_buffer[c]>='a' && read_buffer[c]<='z')
			{
				read_buffer[c]=toupper(read_buffer[c]);
			}
			else if(read_buffer[c]>='A' && read_buffer[c]<='Z')
			{
				read_buffer[c]=tolower(read_buffer[c]);
			}
			c++;
		}
		printf("RECEIVER:\n");
		printf("Received Message: %s \n", read_buffer);

	}
	return(0);
}