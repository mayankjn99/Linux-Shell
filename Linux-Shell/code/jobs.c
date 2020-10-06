#include "headers.h"
void listjob(int l)
{
    pid_t pid=jobs[l].PID;

    char name[100];
    strcpy(name,jobs[l].job_name);
    char status[100];
    char filename[1000];
     int unused;
                        char comm[1000];
                        char state;
                    sprintf(filename, "/proc/%d/stat", pid);
                       FILE *f = fopen(filename, "r");
                       
                       
                        if ( f == NULL ) 
                                { 
                                    strcpy(status,"Stopped");
                                } 

                        else{
                   
                         fscanf(f, "%d %s %c", &unused, comm, &state);
                     }
                         if(state=='S'|| state =='R')
                            strcpy(status,"Running");
                           
                        else
                             strcpy(status,"Stopped");
                            
                       

     printf("[%d] %s %s [%d]\n",l+1, status, name, pid);


}