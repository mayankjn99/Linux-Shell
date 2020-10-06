#include "headers.h"
void removepid(int index)
{
	int i=index;
	back_g--;
    while(i< back_g)
     {
     	  jobs[i].PID = jobs[i+1].PID;
          strcpy(jobs[i].job_name, jobs[i+1].job_name);
          i++;
     }
     return;
}
void front(char para[][1024], int count)
{
    if(count==2)
    {  
    int pid;
    int  job_no ;

    int  status;
    job_no=atoi(para[1]);
    pid = jobs[job_no-1].PID;
    CHILD_ID = pid;

    int dif=back_g-job_no;
	if (dif<0 || job_no <=0)
	{
		printf("Enter valid job number.");
		return;
	}
	
	strcpy(CURR_JOB, jobs[job_no-1].job_name);
	removepid(job_no-1);
		kill(pid, SIGCONT); 
	signal(SIGTTIN, SIG_IGN);
	
	signal(SIGTTOU, SIG_IGN);
	 tcsetpgrp(STDIN_FILENO, CHILD_ID); 
	// printf("%d",pid);

	
	waitpid(pid, &status, WUNTRACED);
	pid=0;
	tcsetpgrp(STDIN_FILENO, getpgrp()); 
	signal(SIGTTIN, SIG_DFL);
	 signal(SIGTTOU, SIG_DFL); 
	//signal(SIGTSTP, ctrl_z);

		if(WIFSTOPPED(status))
		{
			int index=back_g;
			back_g++;
			printf("%s with PID %d suspended\n", CURR_JOB, CHILD_ID);
			jobs[index].PID = CHILD_ID;
			strcpy(jobs[index].job_name, CURR_JOB);
	        
	        
		}	
	}
	else
	{
		printf("fg requires job number of background process ");
	}

	return;
}
