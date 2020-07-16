//
//  main.c
//  Compress
//
//  Created by Arsalan Iravani on 26/10/2019.
//  Copyright © 2019 Arsalan Iravani. All rights reserved.
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
#include <math.h>
#include <string.h>
#include "color.h"

#ifndef BUFFSIZE
#define BUFFSIZE 1
#endif

char compresionBuffer[10000];
int indexForCompressionBuffer = 0;

void writeComboToBuffer(int numberOfCombo, int value) {
    switch (numberOfCombo) {
        case 1:
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
        case 2:
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
        case 3:
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
        case 4:
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
        case 5:
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
        case 6:
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 0;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
            
        case 7:
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = 1;
            compresionBuffer[indexForCompressionBuffer++] = value;
            break;
        default:
            break;
    }
}

int main (int argc, char **argv) {
    
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
//    if (fd1 > 0 && fd2 > 0)
//        printf(Red"CONTENT :\n");
//    printf(Reset);
    
    int prevMaskingResult = 0b00000000;
    int combo = 0;
    int numberOfBits = 0;
    
    while (read(fd1, buf, BUFFSIZE) > 0) {
        
        int resultAfterMasking = 0b00000000;
        int byte = buf[0];
    
        for (int j = 0; j < 8; j++) {
            
            numberOfBits++;
            
            resultAfterMasking = byte & 0b10000000;
                        
            int resultToWrite = resultAfterMasking == 128 ? 0 : 1;
                        
            if (resultAfterMasking == prevMaskingResult) {
                combo++;

                if (combo == 7) {
                    writeComboToBuffer(combo, resultToWrite);
                    combo = 1;
                }
            } else {    //change
                writeComboToBuffer(combo, resultToWrite);
                combo = 1;
            }
            
            prevMaskingResult = resultAfterMasking;
            byte <<= 1;
        }
    }
    
    compresionBuffer[indexForCompressionBuffer++] = 'e';
    
    // Create compressed file
    
    int i = 0;
    int j = 1;
    
    while (compresionBuffer[i] != 'e') {
        j % 8 == 0 && j != 0 ? printf("%d ", compresionBuffer[i]) : printf("%d", compresionBuffer[i]);
        j++;
        i++;
    }
    
//    int i = 0;
    
    int resultBuffer[1000];
    int resultBufferIndex = 0;
    int resultByte = 0b00000000;
    
    int counter = 1;
    
//    while (compresionBuffer[i] != 'e') {
////        i % 7 == 0 && i != 0 ? printf("%d ", compresionBuffer[i++]) : printf("%d", compresionBuffer[i++]);
//
//        printf("%d\n", compresionBuffer[i]);
//
//        // 0 false, else true
//        if (compresionBuffer[i]) {
//            resultByte <<= 1;
//            resultByte += 1;
//        } else {
//            resultByte <<= 1;
//        }
//
//        if (counter % 8 == 0) {
//            resultBuffer[counter] = resultByte;
//            printf("is: %d\n", resultByte);
//            resultByte = 0b00000000;
//        }
//
//        i++;
//        counter++;
//    }
    
    //    if (write(fd2, compresionBuffer, lengthOfReadingBuffer) != lengthOfReadingBuffer) {
    //          perror("Write Error !");
    //          exit(EXIT_FAILURE);
    //    }
    
    
    printf("\nNumber of bytes:\t%d\n", numberOfBits);
    
    if (fd1 > 0 && fd2 > 0 ) {
        printf("\nDone 👍🏼 \n");
        printf("You can find your file at: 👉🏻\t%s\n", argv[2]);
        printf("Copyright © 2017 Copyright Arsalan Iravani. All Rights Reserved.\n\n");
    } else
        perror("Copy Error !\n");
    
    close(fd1);
    close(fd2);
    
    printf(White);
    
    return 0;
}
