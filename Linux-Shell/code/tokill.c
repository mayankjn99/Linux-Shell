#include "headers.h"
void murder(char para[][1024],int count)
{
	if(count==3){
		int job_no,signal_no;
		job_no=atoi(para[1]);
		signal_no=atoi(para[2]);
		pid_t pid=jobs[job_no-1].PID;
		if(back_g < job_no)
		{
			printf("Invalid job number\n" );
			return ;
		}
		else
		{
			kill(pid,signal_no);
			if(signal_no==9)
			{
				removepid(job_no-1);
			}
		}
	}
	else
	{
		printf("Kill requires job number and signal\n");

	}
return ;

}