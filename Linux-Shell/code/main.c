#include "headers.h"
int processarr[1000];
int counter=0;
int ftq=0;
int toquit=0;

void ctrl_c(int signum)
{
    pid_t p ;
    p=getpid();
    if(p < 0)
        perror("Error");
    
    else if (p != SHELL_ID)
        return;
// If any process run in foreground
    if(CHILD_ID==-1)
        return ;
    if (CHILD_ID != -1)
        kill(CHILD_ID, SIGINT);        
    
    signal(SIGINT, ctrl_c); 
} 
void ctrl_z(int signum)
 {
  // printf("aaya");
  //printf("%d",CHILD_ID);
    if (CHILD_ID != -1 )
     {
         
         int index=back_g;
         back_g++;
        fflush(stdout); 
        kill(CHILD_ID, SIGTSTP);      
         jobs[index].PID = CHILD_ID;
          strcpy(jobs[index].job_name, CURR_JOB);
     }

     else
     {
        signal(SIGTSTP, SIG_IGN);
        return ;
     }

     signal(SIGTSTP, ctrl_z);
 }
void prompt()
{
    char *DIR;
      getlogin_r(USER, sizeof(USER));
    gethostname(HOST, sizeof(HOST));
   
    if (getcwd(CWD, sizeof(CWD)) == NULL)
    {
       perror("getcwd() error");
       exit(EXIT_FAILURE);
    }

    else
    {
        char * p;
        p = strstr(CWD, HOME);
        if(p==0)
        {
             DIR = CWD;
            printf("<%s@%s:~%s>", USER, HOST, DIR);
          
        }
        else
        {
            
             DIR = p + strlen(HOME);
            printf("<%s@%s:~%s>", USER, HOST, DIR);
        }

    }

    
}
char *get_input()
{
    char *input_line = NULL;
    ssize_t input_size = 0;
    toquit=getline(&input_line, &input_size, stdin);
    return input_line;
}



void performcmd(char *commandtoexe,char* homedir)

{
     
    char *token = (char *)malloc(sizeof(char) *2000);
                strcpy(token,commandtoexe);          //commands[i]
              
                  int count = 0;

                token = strtok(token, " \n\t\r");
           char parameters[100][1024];
           for(int j=0;j<100;j++)
           {
            for(int k=0;k<1024;k++)
                parameters[j][k]='\0';
           }
                      
            while (token!= NULL)
            {
              
            
                strcpy(parameters[count],token);
              //  printf("%s",parameters[count]);
                count++;
                token  = strtok(NULL, " \n\t\r");
            }
            char *command = (char *)malloc(sizeof(char) *2000);
            strcpy(command,parameters[0]);
              //To check redirection
            int r=0,p=0;
            for(int gg=0;gg < count;gg++)
            {
                if(strcmp(parameters[gg],"<")==0|| strcmp(parameters[gg],">")==0|| strcmp(parameters[gg],">>")==0)
                    r=1;
                else if(strcmp(parameters[gg],"|")==0)
                    p=1;
            }
           // printf("%d",r);
            if(p==1)
            {
                piping(commandtoexe,count,parameters);
                return ;
            }
            
            if(r==1)
            {
                performred(count,commandtoexe,parameters);
                return ;
            }

            // starting to test which command to perform 
           

            if(strcmp(command,"echo")==0){
                for(int yum=1;yum<count;yum++)
                printf("%s ",parameters[yum]);
                printf("\n");
            }
            else if(strcmp(command,"overkill")==0)
                destroy();
            else if(strcmp(command,"kjob")==0)
            {
                murder(parameters,count);
            }
            else if(strcmp(command,"fg")==0)
            {
                front(parameters,count);
            }
            else if(strcmp(command,"bg")==0)
                bg(parameters,count);
            else if(strcmp(command,"setenv")==0)
            {
                if(count!=3 && count!=2)
                {
                    printf("Error \n");
                }
                else if(count == 2) 
                    {
                        int r=setenv(parameters[1],"\0",2);
                        if(r < 0)
                            perror("Error");
                    }
                else{
                int r=setenv(parameters[1],parameters[2],2);
                if(r<0)
                    perror("Error");
                }
            }
            else if(strcmp(command,"quit")==0)
            {
                destroy();
                ftq=1;
               // printf("wtf");  
                return;
                
            }
            else if(strcmp(command,"jobs")==0)
            {
                //printf("%d",counter);
                if(back_g==0)
                    printf("No background process\n");
                else{
                for(int l=0;l<back_g;l++)
                {
                    listjob(l);

                }
            }
            }
            else if(strcmp(command,"unsetenv")==0)
            {
                if(count!=2)
                {
                    printf("Error: one argument required \n");
                }
                else{
                    int r=unsetenv(parameters[1]);
                    if(r==-1)
                        perror("Error");
                }
            }
            else if(strcmp(command,"pwd")==0)
            {
                char s[100];
                printf("%s\n", getcwd(s, 100));
            }
            else if(strcmp(command, "pinfo")==0)
                    pinfo(count,parameters,homedir);
           // printf("%s",CWD);
            else if(strcmp(command,"cd")==0)
            {
                cdexe(parameters,homedir);
            }
            else if(strcmp(command,"ls")==0)
            {    
                char *buf=getcwd(buf,100);
                char cmp[100];
                int lit=0,hid=0,lal=0;
                for(int ct=1;ct<count;ct++)
                {
                    if(strcmp(parameters[ct],"-l")==0)
                    {
                        lit=1;
                        lal++;
                    }
                     else if(strcmp(parameters[ct],"-a")==0){
                        hid=1;
                        lal++;
                    }
                     else if(strcmp(parameters[ct],"-al")==0||strcmp(parameters[ct],"-la")==0)
                        lit=hid=1;
                }
                    if(count==1){
                        //listFile(buf);
                        listFile(buf,homedir);
                    } 
                    else{      
                           if(strcmp(parameters[1],".")==0)listFile(buf,homedir);
                           else if(strcmp(parameters[1],"..")==0)listFile(parameters[1],homedir);
                           else if(lit==1 && hid==0)
                           {
                                if(count==2)
                                    ls_l(buf,homedir);             //ls -l
                                else{
                                    for(int ct=2;ct<count;ct++)
                                    {
                                        ls_l(parameters[ct],homedir);
                                    }

                                }

                           }
                           else if(lit==0&&hid==1)
                           {
                                if(count==2)                //ls -a
                                    listFiles(buf,homedir);
                                else
                                {
                                    for(int ct=2;ct<count;ct++)
                                    {
                                        listFiles(parameters[ct],homedir);
                                    }
                                }


                           }
                           else if(lit==1&&hid==1)              //ls -al || ls -la
                           {
                                if(count==2|| (count==3 && lal==2))                //ls -a
                                    ls_al(buf,homedir);
                                else
                                {
                                    int ct=2;
                                    if(lal==2)
                                        ct=3;
                                    else
                                        ct=2;

                                    for(;ct<count;ct++)
                                    {
                                        ls_al(parameters[ct],homedir);
                                    }
                                }

                           }
                           else{
                                for(int ct=1;ct<count;ct++)
                                    listFile(parameters[ct],homedir);


                           }
                       }

            }
            else
            {
                int isbg=0;
                if(strcmp(parameters[count-1],"&")==0)
                    isbg=1;
                execute(count,parameters,isbg);
                
            }
}


int main()
{
     char *DIR;
      char *exe = malloc(sizeof(char) *(100));
    pid_t p_id;
    char *homedir;
   // homedir=getcwd(homedir, 100);

    p_id = getpid();   
    sprintf(exe,"/proc/%d/exe", p_id);
    int ret = readlink(exe, HOME, 1000);
    SHELL_ID = p_id;
    HOME[ret] = '\0';

    int n=strlen(HOME)-1;
    int i=n;
    while(i>=0)
    {
        if(HOME[i] == '/')
        {
            HOME[i] = '\0';
            break;
        }
        i--;
    }
 // printf("%s",HOME );
    homedir=HOME;
    strcpy(prevdir,homedir);
    //printf("%s\n",prevdir );
    int rf=0;
    while(1)
    {
        
        if(rf==1)
            break;
        char *input;
        CHILD_ID=-1;

        prompt();
        input = get_input();
        if(toquit==-1){
            printf("\n");
            destroy();
            break;
        }
        int x=0;
        char *p = strtok (input, ";");
        char **commands = malloc(256 * sizeof(char *));


            while (p != NULL)
            {
                commands[x++] = p;
                p = strtok (NULL, ";");
            }
       //printf("%d",back_g);

           signal(SIGINT, ctrl_c);
              signal(SIGTSTP, ctrl_z);
        for(int i = 0; i < x; i++){

                performcmd(commands[i],homedir);
                if(ftq==1){
                     rf=1;
                    break;
                   
                }
                
        }
            

    } 
    return 0;
}

               
            
               
  