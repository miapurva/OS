#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

void upper_case(char string[])
{
	int c=0;
	while(string[c]!='\0')
	{
		if(string[c]>='a' && string[c]<='z')
		{
			string[c]=string[c]-32;
		}
		c++;
	}
}

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
		printf("Message: %s \n", write_string);
		printf("\n");
		write(fd[1],write_string,sizeof(write_string));
		exit(0);
	}
	else if(pid>0)
	{
		close(fd[1]);
		message=read(fd[0],read_buffer, sizeof(read_buffer));
		upper_case(read_buffer);
		printf("RECEIVER:\n");
		printf("Message: %s \n", read_buffer);

	}
	return(0);
}