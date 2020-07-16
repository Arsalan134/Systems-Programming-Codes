//
//  main.c
//  midterm
//
//  Created by Arsalan Iravani on 17.03.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#define OPT_N 0x01
#define OPT_S 0x02
#define OPT_L 0x04
#define OPT_W 0x08
#define OPT_U 0x10
#define OPT_G 0x20

struct search {
    int mask;
    char *name;
    char *word;
    int uid;
    int gid;
    char cmp;
    int size;
    int symlink;
} options;

void quit(char *msg){
    printf("%s", msg);
    exit(EXIT_SUCCESS);
}

void readargs(int argc, char *argv[]){
    int pos = 1;
    char *arg;
    struct group *grp;
    struct passwd *pwd;
    while (pos < argc) {
        arg = argv[pos++];
        if (strlen(arg) != 2 || arg[0] != '-')
            quit("Wrong option");
        switch (arg[1]) {
            case 'N':
            case 'n':
                options.mask |= OPT_N;
                options.cmp = argv[pos++][0];
                break;
                
            case 'S':
            case 's':
                options.mask |= OPT_S;
                options.name = argv[pos++];
                break;
                
            case 'L':
            case 'l':
                options.mask |= OPT_L;
                options.symlink = 1;
                break;
                
            case 'W':
            case 'w':
                options.mask |= OPT_W;
                options.word = argv[pos++];
                break;
                
                
                
            case 'U':
            case 'u':
                options.mask |= OPT_U;
                pwd = getpwnam(argv[pos++]);
                options.uid = atoi(pwd->pw_uid);
                break;
                
            case 'G':
            case 'g':
                options.mask |= OPT_G;
                grp = getgrnam(argv[pos++]);
                // FIXME: no
//                options.gid = atoi(grp->uid);
                break;
        }
    }
}

void contains(const char *filename, char *str){
    int fd = open(filename, O_RDONLY);
    close(fd);
}

void list(){
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat info;
    
    while ((entry = readdir(dir)) != NULL) {
        char *fname = entry -> d_name;
        if (lstat(fname, &info) < 0) {
            quit("Stat did not work");
        }
        
        if (S_ISDIR(info.st_mode)) {
            chdir(fname);
            list();
            chdir("..");
        }
        
        if (options.mask & OPT_N && !strstr(fname, options.name))
            continue;
        
        if (options.mask & OPT_U && options.uid != info.st_uid)
            continue;
        
        if (options.mask & OPT_G && options.gid != info.st_gid)
            continue;
        
        if (S_ISDIR(info.st_mode) && (options.mask & OPT_L || options.mask & OPT_W || options.mask & OPT_S))
            continue;
        
        if (options.mask & OPT_S) {
            if ((options.cmp == 'L' || options.cmp == 'l') && info.st_size >= options.size)
                continue;
            if ((options.cmp == 'E' || options.cmp == 'e') && info.st_size != options.size)
                continue;
            if ((options.cmp == 'G' || options.cmp == 'g') && info.st_size <= options.size)
                continue;
        }
        
        if ((options.mask & OPT_L) && !S_IFLNK)
            continue;
        
        
        if ((options.mask & OPT_W) && !is_content(fname, options.word))
            continue;
        
        printf("%s\n",fname);
        
    }
}


int main(int argc, const char * argv[]) {
    readargs(argc, argv);
    list();
    return EXIT_SUCCESS;
}













