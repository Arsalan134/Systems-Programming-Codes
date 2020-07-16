//
//  main.c
//  changeDir
//
//  Created by Arsalan Iravani on 01.03.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


int main(int argc, const char * argv[]) {
    
    printf("\n\tBefore\n");
    char buff[PATH_MAX + 1];
    char* cwd = getcwd(buff, PATH_MAX + 1);
    if( cwd != NULL )
        printf("\tMy working directory is %s\n", cwd);
    
    DIR *directory;
    struct dirent *dp;
    
    if (argc == 1)
        directory = opendir(".");
    else
        directory = opendir(argv[1]);
    
    int i = 1;
    printf("\n");
    
    while ((dp=readdir(directory)) != NULL)
        printf("%d\t%s\n", i++, dp->d_name);
    
    closedir(directory);
    
    chdir("/Volumes");
    //    printf("%d\t returned\n" , a);
    
    if (argc == 1)
        directory = opendir(".");
    else
        directory = opendir(argv[1]);
    
    i = 1;
    printf("\n\tAfter\n");
    cwd = getcwd(buff, PATH_MAX + 1);
    if( cwd != NULL )
        printf("\tMy working directory is %s\n\n", cwd);
    
    while ((dp=readdir(directory)) != NULL)
        printf("%d\t%s\n", i++, dp->d_name);
    
    closedir(directory);
    printf("\n");
    
    return EXIT_SUCCESS;
}

