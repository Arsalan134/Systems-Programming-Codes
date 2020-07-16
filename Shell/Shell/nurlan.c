#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#define STDIN_FILENO 0
#define STDOUT_FILENO 1

struct string{
    char* get_string;
    int get_size;
}string;

void ls(){
    //DIR struct opens curent directory and assigns it to the pointer *d
    DIR           *d;
    d = opendir(".");
    
    //struct dirent reads entries from pointer d and assigns them to the pointer *dir
    struct dirent *dir;
    
    //struct stat is needed for checking weather file is directory or not
    //  struct stat st;
    
    if(d){
        while (dir = readdir(d))
            printf("%s\n", dir->d_name);
        closedir(d);
    }
    else printf("opendir error");
}


struct string read_line(){
    struct string str;
    int space = 1;
    char buf[1];
    str.get_string = malloc(space);
    
    str.get_size = 0;
    while(read(STDIN_FILENO, buf, 1)){
        if(buf[0] != '\n'){
            str.get_string[str.get_size++] = buf[0];
            str.get_string = realloc(str.get_string, ++space);
        }
        else break;
    }
    str.get_string[str.get_size] = '\0';
    return str;
}

char* substr(char* in, int begin, int end){
    char* res = malloc(end + 1);
    int i = 0, j = begin;
    while(j < end)
        res[i++] = in[j++];
    res[i] = '\0';
    return res;
}

void shell(){
    int space = 1;
    struct string command;
    int exit = 0;
    while(!exit){
        write(STDOUT_FILENO, "SIMPLE SHELL:~$ ", 16);
        command = read_line();
        
        if(strcmp(command.get_string, "ls") == 0){
            ls();
        }
        else if(strcmp(substr(command.get_string, 0, 3), "cd ") == 0){
            if(chdir(substr(command.get_string, 3, command.get_size)) < 0){
                printf("bash: cd: %s: No such file or directory\n",
                       substr(command.get_string, 3, command.get_size));
            }
        }
        else if(strcmp(command.get_string, "exit") == 0){
            exit = 1;
        }
        else{
            printf("%s: command not found\n", command.get_string);
        }
    }
}

int main(int argc, char const *argv[]) {
    /* code */
    shell();
    return 0;
}
