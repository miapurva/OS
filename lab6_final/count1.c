/*
Usage: gcc count.c -o count
	./count
	I am going to school
she is pretty	

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

void count(char string[])
{
	int wc=0,lc=0,cc=0,i=0;
	while(string[i]!='\0')
	{
		if(string[i]==' ')
		{
			wc++;
			//sprintf()
		}
		else if(string[i]== '.')
		{
			//printf("xkjvbsh\n");
			lc++;
		}
		//else if(string[i]!=' ' || string[i]!= '.')
		else if(isalpha(string[i]))
		{
			cc++;
		}
		i++;
	}
	wc++;
	//lc++;
	printf("\nWord count: %d\n",wc );
    printf("\n\nCharacter count: %d\n",cc );
    printf("\n\nSentence count: %d\n\n",lc );
}

int main(void)
{
	int fd[2],message;
	pid_t pid;
	char write_string[100];
	char read_buffer[100];

	//INPUT
	//fp=fopen(a.txt,"w+");
	printf("Enter the message\t:\n");

	fgets(write_string,100,stdin);
	//scanf("%[^\t]s", write_string);
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
		count(read_buffer);	
		printf("RECEIVER:\n");
		printf("Received Message: %s \n", read_buffer);
			
	}
	//close(fp);
	return(0);
}
