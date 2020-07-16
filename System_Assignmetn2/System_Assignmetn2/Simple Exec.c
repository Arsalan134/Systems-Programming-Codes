//
//  Simple Exec.c
//  System_Assignmetn2
//
//  Created by Arsalan Iravani on 15.04.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

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
 Main function that executes given user command as a command line argument. Simple Exec should wait for user input and execute the command given by the user. The first token in the user input is the command or the executable, all the next tokens are going to be the command line arguments. Tokens consist of alphanumerical characters and symbols. After executing a command, simple should exit with the same exit status as the command itself. In case if the execution  of the command was not successful, this application exits with a status -1.
 @param argc Number of Arguments
 @param argv Arguments
 @return return value of executable
 */
int main(int argc, char *argv[]) {
    
    pid_t pid = fork(); // get id for a child
    
    if (pid == 0) { /* Child process */
        
        char command[100];
        
        command[0] = '\0';

        command = getCommand();
        
//        result = system(command); // Create variable to store exit status of executable
        
        if (WIFEXITED(result))
            WEXITSTATUS(result);
        else{
            result = -1;
        }
        printf("Exit Status:\t%d \t %d\n", WEXITSTATUS(result), WTERMSIG(result));
        
        return result;
        
    } else  /* Parent process */
        waitpid(pid, 0, 0); /* wait for child to exit */
    
    return result;
}












