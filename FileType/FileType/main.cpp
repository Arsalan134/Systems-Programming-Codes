//
//  main.cpp
//  FileType
//
//  Created by Arsalan Iravani on 17.02.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <pwd.h>
#include <grp.h>

#ifndef BUFFSIZE
#define BUFFSIZE 4096
#endif

using namespace std;

int main (int argc, char **argv){
    struct stat sb;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (lstat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    
    printf("\nFile type:\t\t\t");
    
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    
    struct passwd *pw = getpwuid(sb.st_uid);
    printf("Owner \t\t\t\t%s \n" , pw->pw_name);
    
    printf("I-node number:\t\t\t%ld\n", (long) sb.st_ino);
    printf("Mode:\t\t\t\t%lo (octal)\n",(unsigned long) sb.st_mode);
    printf("Link count:\t\t\t%ld\n", (long) sb.st_nlink);
    printf("Ownership:\t\t\tUID=%ld   GID=%ld\n",(long) sb.st_uid, (long) sb.st_gid);
    printf("Preferred I/O block size:\t%ld bytes\n",(long) sb.st_blksize);
    printf("File size:\t\t\t%lld bytes\n",(long long) sb.st_size);
    printf("Blocks allocated:\t\t%lld\n",(long long) sb.st_blocks);
    printf("Last status change:\t\t%s", ctime(&sb.st_ctime));
    printf("Last file access:\t\t%s", ctime(&sb.st_atime));
    printf("Last file modification:\t\t%s\n", ctime(&sb.st_mtime));
    
    exit(EXIT_SUCCESS);
}
