#include <stdio.h>
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

void  parse(char *line, char **argv)
{
    while (*line != '\0') 
    {       /* if not the end of line ....... */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0    */
        *argv++ = line;          /* save the argument position     */
        while (*line != '\0' && *line != ' ' &&  *line != '\t' && *line != '\n') 
            line++;             // skip the argument until ...    
    }
    *argv = '\0';                 // mark the end of argument list  
}
/*
void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     // fork a child process           
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          // for the child process:         
          if (execvp(*argv, argv) < 0) {     // execute the command  
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  // for the parent:      
          while (wait(&status) != pid)       // wait for completion  
               ;
     }
}
*/
void  execute(char **argv, FILE *history)
{
     pid_t  pid;
     int status, correct=0;

    if ((pid = fork()) < 0) 
    {    // fork a child process           
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0) 
    {  // for the child process: 
    	if(*argv[0]=='!')
    	{
    		int m=strlen(argv[0]);
    		char h[m];
    		strcpy(h,argv[0]);
    		int i=m-1,x=0,p=0;
        //to fetch the latest
    		if(h[1]=='!')
    		{
    			struct cmd c;
    			fseek(history, -(sizeof(struct cmd )), SEEK_END);
    			fread(&c,sizeof(x),1,history);
    			printf("%s\n",c.c);
    		}
    		else
    		{
    			while(i>=1)
    			{
    				char c=h[i];
    				x = ((c - '0')* pow(10,p)) + x;	
          			--i;
          			++p;
          			//x=atoi(c);
    			}
    			if(x<=gh)
    			{
      				for (int i = 0; i < x; ++i)
      				{
      					struct cmd c;
                fseek(history, -( (i+1) * sizeof(struct cmd) ), SEEK_END);
  	            fread(&c,sizeof(x),1,history);
  	            printf("%s\n",c.c );
      				}
    			}
    			else
    				printf("ERROR: Number too large \n");
    		}
    	}
        else if (execvp(*argv, argv) < 0) 
        {     // execute the command  
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else 
    { 	//for the parent:      
		while (wait(&status) != pid);       // wait for completion 
		struct cmd c;
		strcpy(c.c, *argv);
		fwrite(&c,1, sizeof(struct cmd), history);
		gh++;
    }
}

void  main(void)
{
    char  line[1024];             /* the input line                 */
    char  *argv[64];              /* the command line argument      */
	gh=0;
	FILE* history = fopen("history.txt", "w+");
    while (1) 
    {   /* repeat until done .... */
        printf("@yutika-> ");     /*   display a prompt             */
        gets(line);              /*   read in the command line     */
        printf("\n");
        parse(line, argv);       /*   parse the line               */
        if (strcmp(argv[0], "exit") == 0)
        {
        	exit(0); 	 				/*   exit if it is    */
        	fclose(history);
        }  								/* is it an "exit"?     */            
        execute(argv, history);         /* otherwise, execute the command */
    }
    fclose(history);
}
