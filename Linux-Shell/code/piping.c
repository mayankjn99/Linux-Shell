#include "headers.h"


void piping(char *command,int count,char para[][1024])
{
   
     int type=0, parr[2], fd=0; 
     int no=0;
    char **pipe_args = malloc(256 * sizeof(char *));
    char *p = strtok (command, "|");
    while (1)
    {
        if(p==NULL)
            break;
        pipe_args[no++] = p;
        p = strtok (NULL, "|");
    }
   
      pid_t newproc;
    for(int j=0; pipe_args[j]!=NULL; j++)
    {
       //  printf("%s",pipe_args[j]);
         if (pipe(parr)==-1) 
            { 
                perror("Error");
                return ;
            } 
        newproc=fork();
        if(newproc < 0)
        {
            perror("Error");
            return ;
        }
        else if(newproc==0)
        {
            
            if(pipe_args[j+1]!=NULL)
             dup2(parr[1],1); 
         dup2(fd , 0);
            close(parr[0]);
            performcmd(pipe_args[j],HOME);
            exit(2);
        }
        else
        {

                waitpid(-1,NULL,0);
            close(parr[1]);
            fd = parr[0];
        }
    }
    
}