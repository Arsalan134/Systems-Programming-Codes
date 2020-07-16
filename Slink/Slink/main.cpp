//
//  main.cpp
//  Slink
//
//  Created by Arsalan Iravani on 20.02.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#ifndef BUFFSIZE
#define BUFFSIZE 20
#endif

int main(int argc, const char * argv[]) {
    printf("\n");
    
    // create file descriptor
    int fdSl = open("sl", O_RDWR);
    int fdFile = open("altunfile.txt", O_RDWR, O_CREAT, 777);
    
    printf("slink %d, file %d \n\n", fdSl, fdFile);
    
    // create buffer
    char bufSl[BUFFSIZE];
    char bufFile[BUFFSIZE];
    
    // fill buffer
    strcpy(bufSl, "<--------------------->");
    strcpy(bufFile, "<--------------------->");
    
    // read link and file
    ssize_t n = readlink("sl", bufSl, BUFFSIZE);
    ssize_t n2 = read(fdFile, bufFile, BUFFSIZE);
    
    bufSl[n] = '\0';
    bufFile[n2] = '\0';
    
    printf("Size of bytes sl:\t\t%zd\n", n);
    printf("Slink Buffer:\t%s\n\n", bufSl);
    
    printf("Size of bytes fdFile:\t\t%zd\n", n2);
    printf("File Buffer:\t%s\n", bufFile);
    
    printf("\n");
    return 0;
}
