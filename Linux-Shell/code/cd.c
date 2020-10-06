#include "headers.h"

void cdexe(char para[][1024],char *homedir)
{

	char temp[1024];
	for(int i=0;i<2048;i++)
		CWD[i] = '\0';
	if(para[1][0]=='-')
	{
		//getcwd(prevdir,2048);
		char temp[2048];
		getcwd(temp,2048);
		int  k =chdir(prevdir);
		strcpy(prevdir,temp);
		getcwd(CWD,2048);
		//printf("%s\n",prevdir);
		printf("%s\n",CWD);
		if(k<0)
		{
			perror("Error");

		}
	}
	else if(para[1][0]!='~')
	{
		getcwd(prevdir,2048);
		int  k =chdir(para[1]);
	

		getcwd(CWD,2048);
		if(k<0)
		{
			perror("Error");

		}
	}
	else
	{
		strcpy(temp,para[1]);
		strcpy(CWD,homedir);
		memmove(temp, temp+1, sizeof(temp));
		strcat(CWD,temp);
		getcwd(prevdir,2048);
		if(chdir(CWD)==-1)
		{
			perror("Error");
		}
	}


}
