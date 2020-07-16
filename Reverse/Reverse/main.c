#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFSIZE
#define BUFFSIZE 1
#endif

int main (int argc, char * argv []) {
    
    ssize_t n;
    char buf[BUFFSIZE];
    
    ssize_t sizeOfAFile = 0;
    
    int fd1 = open(argv[1], O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    
    // Read file length
    while ((n = read(fd1, buf, BUFFSIZE)) > 0) {
        sizeOfAFile += n;
    }
    
    for (int i = 0; i < sizeOfAFile / 2; i++) {
        lseek(fd1, i, SEEK_SET);
        read(fd1, buf, BUFFSIZE);
        
        char temp[BUFFSIZE];
        
        // copy to temp
        lseek(fd1, -BUFFSIZE, SEEK_CUR);
        read(fd1, temp, BUFFSIZE);
        
        // copy to buf
        lseek(fd1, -i - 1, SEEK_END); // go to end
        read(fd1, buf, BUFFSIZE);
        
        lseek(fd1, -i - 1, SEEK_END);
        write(fd1, temp, BUFFSIZE); // write start to end
        
        lseek(fd1, i, SEEK_SET);
        write(fd1, buf, BUFFSIZE); // write end to start
        
    }
    
    close(fd1);
    
    return 0;
}

