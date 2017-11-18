#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


void palindrome(char* s){

    char r[strlen(s)];

    int l = strlen(s);
    for (int i = 0; i <l ; ++i)
    {
        r[i] = s[l-1-i];
    }

    printf("%s\n",r);

    if (strcmp(r,s) == 0)
    {
        printf("\nIt is a Palindrome\n");
    }
    else{
        printf("It is not a palindrome\n");
    }
}

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[100];
        char    readbuffer[80];
        printf("enter string");
        gets(string);
        pipe(fd);

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                
               close(fd[0]);

               printf("\nSending String : ' %s '\n",string);
                
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                close(fd[1]);

                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));

                palindrome(readbuffer);

                printf("\nReceived string: %s\n", readbuffer);
        }

        return(0);
}   