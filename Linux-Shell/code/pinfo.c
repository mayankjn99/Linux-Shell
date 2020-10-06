#include "headers.h"
void pinfo(int count,char para[][1024],char homedir[]){
		if(count==1){
			int pid=getpid(); 
					char filename[1000],mem_file_name[100];
				    sprintf(filename, "/proc/%d/stat", pid);
				    FILE *f = fopen(filename, "r");
				   
				    int unused;
					    char comm[1000];
					    char state;
					    int ppid;
					    long long int vsize;
					    long long int val;
					    int i;
					    fscanf(f, "%d %s %c", &unused, comm, &state);
					        for (i = 4; i < 24; i++) {
						         fscanf(f, "%lld ", &val);
						        if (i == 23) 
						           // printf("Virtual Memory usage: ret[%d] scanned[%d] result[%lld]\n", ret, i, val);
						        	vsize=val;
						        }

					   /* char buf[100]=" ";
					    sprintf(mem_file_name, "/proc/%d/mem", pid);
					    FILE *f1 = fopen(filename, "r");
				   		fscanf(f1,"%s",buf);*/
						        char ptg[100]=" "; char buf[100]=" ";
						        sprintf(ptg,"/proc/%d/exe",pid);
						       
						    int siz = readlink(ptg,buf , 100); 

    				printf("pid -- %d\n",pid);
					printf("Process Status -- %c\n",state);
					printf("memory -- %lld\n",vsize);
					if(siz < 0) {
						printf("Access denited to executable path\n");
						
					}
					else {
						buf[siz] = '\0';
						if(strlen(buf) > strlen(homedir) && strncmp(buf,homedir,strlen(homedir)) == 0)
							printf("Executable Path -- ~%s\n",buf + strlen(homedir));  
						else
							printf("Executable Path -- %s\n",buf);
						
					}
					fclose(f);
					//fclose(f1);
				}
				else
				{
					 int id=0;
					for(int i=0;i<strlen(para[1]);i++)
					{	

					// printf("%c",parameter[i]);
						id=id*10+(para[1][i]-'0');
						// printf(" %lld",id);

					}
					
					
					char filename2[1000];
				    sprintf(filename2, "/proc/%d/stat", id);
				    FILE *f1 = fopen(filename2, "r");
				   
				    int unused;
					    char comm[1000];
					    char state;
					    int ppid;
					    long long int vsize=0;
					    long long int val;
					    char buf[100]=" ";
					    int i;
					    fscanf(f1, "%d %s %c", &unused, comm, &state);
					       for (i = 4; i < 24; i++) {
						         fscanf(f1, "%lld ", &val);
						        if (i == 23) 
						           // printf("Virtual Memory usage: ret[%d] scanned[%d] result[%lld]\n", ret, i, val);
						        	vsize=val;
						        }
						              char ptg[100]=" ";
						        sprintf(ptg,"/proc/%d/exe",id);

						 int siz=readlink(ptg,buf , 100); 
						
					   /* char buf[100]=" ";
					    sprintf(mem_file_name, "/proc/%d/mem", pid);
					    FILE *f1 = fopen(filename, "r");
				   		fscanf(f1,"%s",buf);*/

					printf("pid -- %d\n",id);
    			
					printf("Process Status -- %c\n",state);
					printf("memory -- %lld\n",vsize);
					if(siz < 0) {
						printf("Access denited to executable path\n");
						
					}
					else {
						buf[siz] = '\0';
						if(strlen(buf) > strlen(homedir) && strncmp(buf,homedir,strlen(homedir)) == 0)
							printf("Executable Path -- ~%s\n",buf + strlen(homedir));  
						else
							printf("Executable Path -- %s\n",buf);
						
					} 
					fclose(f1);
				

					
				}
		
	}