#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include <fcntl.h>
#include <time.h> 
#include <locale.h> 
#include <sys/utsname.h> 
//#include <perror.h>

#define EXIT_FAILURE 1

char HOST[1024], USER[1024], CWD[2048], HOME[2048],prevdir[2048];
int SHELL_ID,CHILD_ID;
struct bg_job
{
    char job_name[300];
    pid_t PID;  
}jobs[100];
int back_g;
//pid_t CHILD_ID=-1;
char CURR_JOB[2000];

void prompt();
void pinfo(int count,char para[][1024],char *homedir);
void cdexe(char para[][1024],char *homedir);
void ls_l(char path[],char homedir[]);
void listFile( char *path,char *homedir);
void ls_al(char path[],char homedir[]);
void listFiles( char *path,char *homedir);
void performred(int count,char *command,char para[][1024]);
void piping(char *command,int count,char para[][1024]);
void listjob(int l);
void execute(int count,char para[][1024],int isbg);
void murder(char para[][1024],int count);
void destroy();
void front(char para[][1024],int count);
void bg(char para[][1024], int count);
void removepid(int no);
void performcmd(char *commandtoexe,char* homedir);
void  destroy();
void ctrl_z(int signum);

#endif