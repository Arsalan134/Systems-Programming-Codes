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

int numberOfPresses = 0; // number of taps
int seconds = 5;         // timeout

#ifndef BUFFSIZE
#define BUFFSIZE 100
#endif

char buf[BUFFSIZE];


/**
 This function resets global numberOfPresses after 5 seconds
 @param signalNumber 14,
 In order to see signal number hold cmd(Mac OS) or ctrl and click to SIGALRM
 */
void  alarmHandler(int signalNumber){
    numberOfPresses = 0;
    printf("\nCounter is resetted 🎬 \n\n");
}

/**
 This function is called whenever you press ctrl+\
 @param signalNumber 3,
 In order to see signal number hold cmd(Mac OS) or ctrl and click to SIGQUIT
 */
void quitHandler(int signalNumber){
    printf("\nPressed Ctrl+\\ \n\n");
    
    // Increment counter whenever ctrl+\ is pressed
    numberOfPresses++;
    
    // Check how many times ctrl+\ is pressed
    if (numberOfPresses == 1) {
        printf("Started alarm ⏰ \n\n");

        alarm(seconds);         // Set number of seconds. As soon as time is exeeded alarmHandler function is called
    } else if (numberOfPresses >= 2) {
        printf("\nExitting... \n\n");
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, const char * argv[]) {
    
    printf("Hello 🤗 , Program is running...\n");
    printf("Press ctrl+\\ to quit, Press ctrl+c to terminate \n");
    
    // Setup handlers
    signal(SIGQUIT, quitHandler);
    signal(SIGALRM, alarmHandler);
    
    while(1) {
        fgets(buf, BUFFSIZE, stdin);
        write(STDOUT_FILENO, buf, sizeof(buf));
    }
    return EXIT_SUCCESS;
}




