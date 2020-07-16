//
//  main.c/Users/Arsalan/Documents/Xcode Projects/System Assignment 1/System Assignment 1/concat.c
//  elshad
//
//  Created by Arsalan Iravani on 23.03.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/// Concatenate 2 strings
char *concat(char *format, ...){
    
    size_t len = 0;
    char *retbuf = "";
    va_list argp;
    char *p;
    
    if(format == NULL)
        return NULL;
    
    len = strlen(format);
    va_start(argp, format);
    
    while((p = va_arg(argp, char *)) != NULL){
        len += strlen(p);
    }
    
    va_end(argp);
    retbuf = malloc(0);
    
    if(retbuf == NULL)
        return NULL;
    
    strcpy(retbuf, format);
    
    va_start(argp, format);
    p = va_arg(argp, char *);
    while(p != NULL){
        strcat(retbuf, p);
        p = va_arg(argp, char *);
    }
    va_end(argp);
    return retbuf;
}

int main(){
    concat("asd","hh");
    return 0;
}
