#include "headers.h"
void listFiles( char *path,char *homedir)
{
    if(strcmp(path,"~")==0)
    {/*
        char h[100]="/home/";
        char username[100];
        getlogin_r(username, 100);
        strcat(h,username);
        strcpy(path,h);*/
        path =homedir;
    }
    struct dirent *dp;
    DIR *dir = opendir(path);

    // Unable to open directory stream
    if (!dir) 
        {
            perror("Error");
            return;
        }

    while ((dp = readdir(dir)) != NULL)
    {
        //char co[100],ch='.';
        //strcpy(co,dp->d_name);
        //printf("%s",co);
        //if(co[0]!=ch)
        printf("%s ", dp->d_name);
        
    }

        printf("\n");
    
    // Close directory stream
    closedir(dir);
}
/*
void list( char *path,char para)
{

    struct dirent *dp;
    DIR *dir = opendir(path);

    // Unable to open directory stream
    if (!dir) 
        return; 

    while ((dp = readdir(dir)) != NULL)
    {
        
        printf("%s ", dp->d_name);
    }

    // Close directory stream
    closedir(dir);
}*/