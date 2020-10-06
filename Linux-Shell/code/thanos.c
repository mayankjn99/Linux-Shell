#include "headers.h"

void destroy()
{
	int j=back_g;
	while(j--)
	{
		pid_t pid=jobs[j].PID;
		kill(pid,9);
	}
	back_g=0;
	return ;
}