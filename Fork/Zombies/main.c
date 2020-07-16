//
//  main.c
//  Fork
//
//  Created by Arsalan Iravani on 11.04.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    
    int pid = fork();               // parent gets pid of child. Child gets 0
    
    if (pid < 0)
        exit(EXIT_FAILURE);
    else if (pid == 0) {            // child
        printf("\t\tChild\n");
        printf("I'm a child, my process id:\t\t%d\n", getpid());
        
        int parent = getppid();
        
        parent == 1 ? printf("I'm an orphan\n") : printf("My parent's process id:\t\t\t%d\n", getppid());
        
        exit(EXIT_SUCCESS);
    } else {                         // parent
        printf("\t\tParent\n");
        
        printf("Waiting for child to complete\n");
        
        int exit_status;
        wait(&exit_status);
        
        printf("\t\tParent\n");
        
        printf("I am a parent, my process id:\t\t%d\n", getpid());
        printf("My child's process id:\t\t\t%d\n\n", pid);
        
        if (WIFSIGNALED(exit_status))
            printf("Signal has interrupted the child:\t%d\n", WTERMSIG(exit_status));
        
        printf("My child exited with status:\t%d\n\n", WEXITSTATUS(exit_status));
    }
    
    return EXIT_SUCCESS;
}







