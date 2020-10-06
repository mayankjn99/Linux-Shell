#include "headers.h"
void func(int signum)
{

    int j=back_g,stat;
            while(j--)
            {
                pid_t pid=jobs[j].PID;
                pid=waitpid(pid,&stat,WNOHANG );
                if(pid > 0)
                {
                 if (WIFEXITED(stat)) {
                         printf("%s with pid %d exited normally \n",jobs[j].job_name,pid);             
                 }
                 else if(!WIFSTOPPED(stat))
                         printf("%s with pid %d exited abnormally\n ",jobs[j].job_name,pid);
                }             
            }
}
void execute(int count,char para[][1024],int isbg)

{

	pid_t pid=fork(),wpid;
	int status;
	if(pid <0 )
		perror("Error");
	else if(pid==0)
	{
   // if(isbg==1)
      setpgid(0,0);
    char *args[100];
    for(int i=0;i<count;i++)
    {
      if(strcmp(para[i],"&")!=0)
      args[i]=para[i];
    }
    if(isbg)args[count-1]=NULL;
    else
      args[count]=NULL;
		
		int exec=execvp(args[0], args);
          if (exec < 0) 
          {     
               perror("Command not found");
               exit(EXIT_FAILURE);
          }
	}
	else
	{
		if(isbg==1)
		{
     // setpgid(pid,pid);
			strcpy(jobs[back_g].job_name, para[0]);
               int i=1;
               while(i < count-1)
               {
                    strcat(jobs[back_g].job_name, " ");
                    strcat(jobs[back_g].job_name, para[i]);
                    i++;
               }
               signal(SIGCHLD,func);   

               jobs[back_g].PID = pid;
               back_g++;
               printf("[%d] %d\n", back_g, pid);
		}
		else
		{

                strcpy(CURR_JOB, para[0]);
               int i;
               for(i = 1; i < count; i++)
               {
                    strcat(CURR_JOB, " ");
                    strcat(CURR_JOB, para[i]);
               }
                CHILD_ID=pid;
              
              
               // signal(SIGTTIN, SIG_IGN);
  
                //signal(SIGTTOU, SIG_IGN);
                //tcsetpgrp(STDIN_FILENO, CHILD_ID); 

                  signal(SIGTSTP, ctrl_z);
   
		            	wpid = waitpid(pid, &status, WUNTRACED);
                 // tcsetpgrp(STDIN_FILENO, getpgrp()); 
                  //signal(SIGTTIN, SIG_DFL);
                   //signal(SIGTTOU, SIG_DFL); 
                

                
		}
	}

}