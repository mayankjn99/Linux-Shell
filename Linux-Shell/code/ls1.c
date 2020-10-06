#include "headers.h"
void listFile( char *path,char *homedir)
{
    if(strcmp(path,"~")==0)
    {
       path=homedir;
    }
    // printf("%s",path);
    struct dirent *dp;

    DIR *dir = opendir(path);

    // Unable to open directory stream
    if (!dir) {
        perror("error");
        return; 
    }

    while ((dp = readdir(dir)) != NULL)
    {
        char co[100],ch='.';
        strcpy(co,dp->d_name);
       // printf("%s",co);
        if(co[0]!=ch)
        printf("%s ", co);

    }
        printf("\n");
    // Close directory stream
    closedir(dir);
}
