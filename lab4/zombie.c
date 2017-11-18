#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    // Fork returns process id
    // in parent process
    pid_t child_pid = fork();
 
    // Parent process 
    if (child_pid > 0)
        {
            printf("I'm in parent process\n");
           sleep(1);
           printf("I'm still in the parent process\n");      
        }
 
    // Child process
    else  if(child_pid==0)   
    {
        printf("I'm in Child process\n"); 
        exit(0);
              
    } 
 
    return 0;
}