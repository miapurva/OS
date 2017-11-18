#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
    // Create a child process      
    int pid = fork();
 
    if (pid > 0)
    {
        printf("I'm in parent process\n");
        printf("Parent process ending\n");
    }
    
 
    // Note that pid is 0 in child process
    // and negative if fork() fails
    else if (pid == 0)
    {
        sleep(1);
        printf("I'm include child process\n");
        printf("Child process ending\n");
    }
 
    return 0;
}