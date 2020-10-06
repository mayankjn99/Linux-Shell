#include "headers.h"

void bg(char para[][1024], int count)
{
    int jobno=atoi(para[1]);
	if(jobno >back_g)
	{
		printf("No job exits\n");
	}
	else
	{
			pid_t pid = jobs[jobno-1].PID;
			
			//		
			kill(pid,SIGTTIN);
			kill(pid,SIGCONT);
			
	}

	
    
}	