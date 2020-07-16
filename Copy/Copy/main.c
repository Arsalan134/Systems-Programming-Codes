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
#include "color.h"

#ifndef BUFFSIZE
#define BUFFSIZE 4096
#endif

int main (int argc, char **argv){
    
    //    string regularColors[8];
    //
    //    regularColors[0] = Black;
    //    regularColors[1] = Red;
    //    regularColors[2] = Green;
    //    regularColors[3] = Yellow;
    //    regularColors[4] = Blue;
    //    regularColors[5] = Purple;
    //    regularColors[6] = Cyan;
    //    regularColors[7] = White;
    
    //    printf("%s %s", regularColors[0].c_str() , regularColors[1].c_str());
    
    ssize_t n;
    char buf[BUFFSIZE];
    printf("\n");
    
    if (argc > 0)
        for (int i=0; i<argc; i++)
            printf("Argument %d:\t\t%s\n", i, argv[i]);
    
    int fd1 = open(argv[1], O_RDONLY                      , S_IRWXU | S_IRWXG | S_IRWXO);
    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC  , S_IRWXU | S_IRWXG | S_IRWXO);
    
    printf(Cyan"\nFile Descriptor 1:\t%d\n",fd1);
    printf("File Descriptor 2:\t%d\n\n",fd2);
    
    printf(White);
    if (fd1 > 0 && fd2 > 0)
        printf(Red"CONTENT :\n");
    printf(Reset);
    
    while ((n = read(fd1, buf, BUFFSIZE)) > 0) {
        if (write(fd2, buf, n) != n) {
            perror("Write Error !");
            exit(1);
        }else
            printf("%s\n", buf);
    }
    
    if (fd1 > 0 && fd2 > 0 ) {
        printf("Done 👍🏼 \n");
        printf("You can find your file at: 👉🏻\t%s\n", argv[2]);
        printf("Copyright © 2017 Copyright Arsalan Iravani. All Rights Reserved.\n\n");
    } else
        perror("Copy Error !\n");
    
    //    +1MB   =   1000000
    //    +10MB  =   10000000
    //    +100MB =   100000000
    //    +1GB   =   1000000000
    //    +10GB  =   10000000000
    //    +100GB =   100000000000
    
    lseek(fd2, 1000000000, SEEK_SET);
    write(fd2, buf, 1);
    
    close(fd1);
    close(fd2);
    
    printf(White);
    
    
    return 0;
}

