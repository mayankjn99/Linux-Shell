#include "headers.h"


int check(int count,char para[][1024],char *s)
{
     for(int gg=0;gg < count;gg++)
            {
                if(strcmp(para[gg],s)==0)
                        return 1;
            }
            return 0;
           
}
int isfile(char* path) 
{
     FILE *file;
   if (file = fopen(path, "r")) {
      fclose(file);
      return 1;
   } 
   return 0;
}


void performred(int count,char *command,char para[][1024])
{

    char *output[2], *input[2];
    char * out_file = NULL;
    char * in_file = NULL;
    int out_type = 0;
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    int status;


    int in = check(count,para,"<");
    int  v1= check(count,para,">>");
    if(v1==1)
        out_type=2;
    int v2=check(count,para,">");
    if(v2==1)
        out_type=1;

       //char **args = (char**)malloc(sizeof(char*) * 300);
    char *args[1024];
    int no_args = 0;
    if(out_type)
    { 
        for(int gg=0;gg < count; gg++)
        {
            if(strcmp(para[gg],">")==0|| strcmp(para[gg],">>")==0)
                {
                    gg++;
                    out_file=para[gg];
                    //printf("%s",out_file);
                }
            else
            {

                args[no_args]=para[gg];
               // printf("%s",para[gg]);
                no_args++;
            }


        }
         if(out_file == NULL)
        {
            printf("Enter output file\n");
            return;
        }


      
    }
        args[no_args] = NULL;

    if(in)
    { 
         for(int j=0; j < no_args; j++)
            args[j]='\0';
        
        no_args=0;
         for(int gg=0;gg < count; gg++)
        {
            if(strcmp(para[gg],"<")==0)
                {
                    gg++;
                    in_file=para[gg];
                    break;
                }
            else
            {
                args[no_args]=para[gg];
                no_args++;
            }


        }
          args[no_args] = NULL;
         if(in_file == NULL)
        {
            printf("No file input file name\n");
            return;
        }
        
        if(!isfile(in_file))
        {
            printf("File does not exist\n");
            return;
        }
        
    }
      

    pid_t pid = fork();
    int fd1,fd2;
    if(pid < 0)
    {
        perror("Error ");
        return;
    }
    else if(pid == 0)
    {
        
        if(out_type)
        {
            if(out_type == 1){
                fd1 = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if(fd1< 0)
                    {
                        perror("Error");
                    }
            
            }

            else if(out_type == 2){
                fd1 = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if(fd1< 0)
                        {
                            perror("Error");
                        }
            
            }

            
            dup2(fd1, 1);         
            close(fd1);
        }
        if(in)
        {
            fd2 = open(in_file, O_RDONLY);
            if(fd2< 0) 
            {
                perror("Error");
            }   
            
            dup2(fd2, 0);
            close(fd2);
        }
        
        if (execvp(args[0], args) < 0) 
        {     
            perror("Error");
            
        }
        
         dup2(saved_stdout, 1);
        close(saved_stdout);
        dup2(saved_stdin, 0);
        close(saved_stdin);
        
       
    }        
    
    else 
        while (wait(&status) != pid);
    int j=0;
    while(j<no_args){
      args[j]='\0';
      j++;
    }
}