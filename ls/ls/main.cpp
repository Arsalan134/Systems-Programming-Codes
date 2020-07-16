//
//  main.cpp
//  ls
//
//  Created by Arsalan Iravani on 24.02.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, const char * argv[]) {
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
    printf("\n");
    return 0;
}


