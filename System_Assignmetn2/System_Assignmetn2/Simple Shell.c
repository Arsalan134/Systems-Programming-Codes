//
//  Simple Shell.c
//  System_Assignmetn2
//
//  Created by Arsalan Iravani on 17.04.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

/*
 The next task is to extend the first one by making it possible to execute commands, not just once, but repeatedly, until user prints exit. The shell should work like /bin/sh, except you don’t need to implement pipes, forwarding, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

char *PATH = "/bin:/usr/bin:/usr/local/bin/:.";
char *PATHArsalan = "/bin/sh";

int result = -1;

/**
 Main method
 @param argc Number of Arguments
 @param argv Arguments
 @return return value of executable
 */

int main(int argc, char *argv[]) {
    
    //    pid_t pid = fork(); // get id for a child
    
    //    if (pid == 0) { /* Child process */
    char *c = NULL;
    scanf("%c",c);
    printf("Salam\n");
    printf("Scanned:\t%s\n", c);
    
    while (!(strcmp(c, "exit") == 0)) {
        char command[100];
        
        command[0] = '\0';
        
        // Concatenate arguments into one string
        for(int i = 1; i < argc; i++) {
            strcat(command, " ");
            strcat(command, argv[i]);
        }
        
        result = system(command); // Create variable to store exit status of executable
        
        scanf("%s",c);
        printf("Salam\n");
        printf("Scanned:\t%s\n", c);
    }
    
    if (WIFEXITED(result))
        WEXITSTATUS(result);
    else{
        result = -1;
    }
    printf("Exit Status:\t%d \t %d\n", WEXITSTATUS(result), WTERMSIG(result));
    
    return result;
    
    //    } else  /* Parent process */
    //        waitpid(pid, 0, 0); /* wait for child to exit */
    //    cntl slash  within 5 sec twice

}





