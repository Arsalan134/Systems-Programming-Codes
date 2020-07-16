//
//  main.c
//
//  Created by Arsalan Iravani on 19.04.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFSIZE
#define BUFFSIZE 500
#endif

char buf[BUFFSIZE];

short sigInterupt = 0;
short sigQuit = 0;
short sigTerminate = 0;

/**
 This function catches a signal and switches on appropriate boolean

 @param signalNumber Signal number
 */
void signalHandler(int signalNumber){
    if (signalNumber == SIGINT) {
        printf("\n\t\tSIGINT\n\n");
        sigInterupt = 1;
    } else if (signalNumber == SIGQUIT) {
        printf("\n\t\tSIGQUIT\n\n");
        sigQuit = 1;
    } else if (signalNumber == SIGTERM) {
        printf("\n\t\tIGTERM\n\n");
        sigTerminate = 1;
    }
}

int main(int argc, const char * argv[]) {
    
    // Setup handlers for signals
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    ssize_t lengthOfReadingBuffer;
    char buf[BUFFSIZE];
    
    if (argc > 0)
        for (int i=0; i<argc; i++)
            printf("Argument %d:\t\t%s\n", i, argv[i]);
    
    int fd1 = open(argv[1], O_RDONLY                      , S_IRWXU | S_IRWXG | S_IRWXO);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC  , S_IRWXU | S_IRWXG | S_IRWXO);
    
    printf("\nFile Descriptor 1:\t%d\n",fd1);
    printf("File Descriptor 2:\t%d\n\n",fd2);
    
    while ((lengthOfReadingBuffer = read(fd1, buf, BUFFSIZE)) > 0) {
        sleep(1); //  MARK: Simulate long copying
        if (write(fd2, buf, lengthOfReadingBuffer) != lengthOfReadingBuffer) {
            perror("Write Error !");
            exit(1);
        }
    }
    
    write(fd2, "\n", 1);
    
    if (fd1 > 0 && fd2 > 0 ) {
        printf("Done 👍🏼\n");
        printf("You can find your file at: 👉🏻\t%s\n", argv[2]);
        printf("Copyright © 2017 Copyright Arsalan Iravani. All Rights Reserved.\n\n");
    } else
        perror("Copy Error !\n");
    
    close(fd1);
    close(fd2);
    
    if (sigInterupt) {
        signal(SIGINT, SIG_DFL);
        raise(SIGINT);
    } else if (sigQuit) {
        signal(SIGQUIT, SIG_DFL);
        raise(SIGQUIT);
    } else if (sigTerminate) {
        signal(SIGTERM, SIG_DFL);
        raise(SIGTERM);
    }

    return EXIT_SUCCESS;
}












