#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <strings.h>

FILE *history;
int gh;
struct cmd
{
	char c[1024];
};

void parse(char *line,char **argv)
{
	while(*line!='\0')
	{
		while(*line==' ' || *line== '\n' || *line=='\t')
		{
			*line++='\0';
		}
		*argv++=line;
		while(*line!='\0' || *line!=' ' || *line!='\n'|| *line!='\t')
			line++;
	}
	*argv='\0';
}

void execute(char **argv, FILE *history)
{
	pid_t pid;
	int status;

	if((pid=fork)<0)
	{
		perror("Fork unsuccessful\n");
		exit(1);
	}
	else if(pid==0)
	{
		if(*argv[0]=='!')
		{
			int m=strlen(argv[0]);
			char h[m];
			strcpy(h,argv[0]);
			int i=m-1;
			//to fetch the latest
			if(h[1]=='!')
			{
				struct cmd c;
				fseek(history, -(sizeof(struct cmd )), SEEK_END);
				fread(&c,sizeof(x),1,history);
				printf("%s\n",c.c );
			}
			else
			{
				while(i>=1)
				{
					char c=h[i];
					x=((c-'0')*pow(10,p))+x;
					i--;
					p++;

				}
				if(x<=gh)
				{
					for (int i = 0; i < x; ++i)
					{
						struct cmd c;
						fseek(history,-((i+1)*sizeof(struct cmd)), SEEK_END);
						fread(&c,sizeof(x),1,history);
						printf("%s\n", c.c);
					}
						
				}
				else
					printf("Error number too large\n");
			}

		}
		else if(execvp(*argv, argv)<0)
		{
			printf("*** ERROR: exec failed\n");
            exit(1);
		}
	}
	else
	{
		while(wait(&status)!=pid)
			;
		struct cmd c;
		strcpy(c.c,*argv);
		fwrite(&c,1,sizeof(struct cmd),history);
		gh++;
	}
}

int main(void)
{
	char line[1024];
	char *argv[64];
	FILE *history=fopen("history123.txt","w+");
	gh=0;
	while(1)
	{
		printf("@Yutika--> \n");
		gets(line);
		printf("\n");
		parse(line,argv);
		if(strcmp(argv[0],"exit")==0)
		{
			exit(0);
			fclose(history);
		}
		execute(argv,history);
	}
	fclose(history);
	return(0);
}