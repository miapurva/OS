#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2],message;
	pid_t pid;
	char write_string[100];
	char read_buffer[100];

	printf("Enter the message\t:\n");
	fgets(write_string,100,stdin);
	//printf("%s\n", write_string);
	pipe(fd);
	pid=fork();

	if(pid<0)
	{
		perror("Fork unsuccessful\nTerminating unsuccessfully!\n");
		exit(1);
	}
	else if(pid==0)
	{
		//child block will send the message(WRITE)
		//closing the unused(READ) end
		close(fd[0]);
		printf("\n SENDER: \n");
		printf("%s\n", write_string);
		printf("\n");
		write(fd[1],write_string, sizeof(write_string));
		exit(0);
	}
	else if(pid >0)
	{
		//child block will send the message(READ)
		//closing the unused(WRITE) end
		wait(NULL);
		close(fd[1]);
		message=read(fd[0], read_buffer, sizeof(read_buffer));
		printf("RECEIVER: \n");
		
		printf("%s\n", read_buffer);
		printf("\n");
		//exit(0);
	}
	return(0);
}