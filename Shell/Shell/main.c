//
//  main.c
//  Shell
//
//  Created by Arsalan Iravani on 01.03.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include "color.h"

#define SHELL_COLOR "\033[0;97m"
#define shellChar "# "

const int s = 7;
const char * colors[s] = {Red, Yellow, Green, White, Cyan, Blue, Purple};
int colorArrayIndex = 0;    // Declared as global in order to print each time different colors

char* substr(char in[], int begin, int end){
    char* res = malloc(end + 1);
    int i = 0, j = begin;
    while(j < end)
        res[i++] = in[j++];
    res[i] = '\0';
    return res;
}

// *--------------------------------------------------------------------------------------  WRONG DIRECTORY  -------------------
void wrongDirectory(){
    printf(High_Intensity_Red"Wrong directory ❗️\n"SHELL_COLOR);
}

// *--------------------------------------------------------------------------------------  PRINT COLORIZED  -------------------
int lineNumber = 1;
void printColorized(char* string){
    printf("%s%d %s\t\n"SHELL_COLOR, colors[colorArrayIndex], lineNumber++, string);
    colorArrayIndex++;
    colorArrayIndex %= s;
}

// *-------------------------------------------------------------------------------------------   LIST   -----------------------
void list(char argv[]){
    printf("\n");
    
    DIR *directory;
    struct dirent *dp;
    
    if ((directory = opendir(&argv[0]))){
        while ((dp=readdir(directory)) != NULL){
            if (strcmp(substr(dp->d_name, 0, 1), "."))
                printColorized(dp->d_name);
        }
        lineNumber = 1;
        closedir(directory);
    }else
        wrongDirectory();
    printf("\n"SHELL_COLOR);
}

// *-----------------------------------------------------------------------------------  PRINT CURRENT DIRECTORY  --------------
void printCurrentDirectory(){
    char buff[PATH_MAX + 1];
    char* cwd = getcwd(buff, PATH_MAX + 1);
    printf(Yellow"\nYou are in:\t%s\n"SHELL_COLOR, cwd);
}

// *-------------------------------------------------------------------------------------------   CD   -------------------------
void changeDirectory(char argv[]){
    char buff[PATH_MAX + 1];
    char* cwd = getcwd(buff, PATH_MAX + 1);
    DIR *directory;
    
    
    if(strcmp(&argv[0], ".") == 0)
        printCurrentDirectory();
    else if ((directory = opendir(&argv[0]))) {
        printf(High_Intensity_Cyan"\nBefore:\t%s", cwd);
        chdir(&argv[0]);
        cwd = getcwd(buff, PATH_MAX + 1);
        printf(High_Intensity_Green"\nAfter:\t%s\n", cwd);
        closedir(directory);
    }else{
        printf("\n");
        wrongDirectory();
    }
    printf("\n"SHELL_COLOR);
}

// *-------------------------------------------------------------------------------------------  HELP  -------------------------
void help(){
    const int n = 4;
    char * commands[n] = {"list \t\t List all Entries", "cd \t\t Change Directory", "cdir \t\t Current Directory", "exit(e)"};
    printf("\nPossible commands are:\n\n");
    for (int i=0; i < n; i++)
        printColorized(commands[i]);
    lineNumber = 1;
    printf("\n");
}

// *---------------------------------------------------------------------------------------  INTRODUCTION  ---------------------
void introduction(){
    printf(High_Intensity_White"\n\t👋🏻  Welcome to Arsalan's shell  😇\n\n");
    printf("Type ");
    printf(Underline_Cyan"help"SHELL_COLOR);
    printf(" to begin\n\n");
}

// *-------------------------------------------------------------------------------------------   MAIN   -----------------------
int main(int argc, const char * argv[]) {
    
    char cmd[100];
    char arg1[100];
    
    introduction();
    
    printf("%s ", shellChar);
    scanf("%s", cmd);
    
    // Main Loop
    while (strcmp(cmd, "e") != 0 && strcmp(cmd, "exit") != 0) {
        if (strcmp(cmd, "list") == 0){
            scanf("%s",arg1);
            list(arg1);
        }
        else if (strcmp(cmd, "cd") == 0){
            scanf("%s", arg1);
            changeDirectory(arg1);
        }
        else if(strcmp(cmd, "help") == 0)
            help();
        else if(strcmp(cmd, "cdir") == 0){
            printCurrentDirectory();
            printf("\n");
        }
        else
            fprintf(stderr, High_Intensity_Red"\nNo such command ❗️\n\n"SHELL_COLOR);
        printf("%s ", shellChar);
        scanf("%s", cmd);
    }
    
    printf(High_Intensity_Red"\n⛔️\tEXIT...\n\n"Reset);
    return EXIT_SUCCESS;
}
