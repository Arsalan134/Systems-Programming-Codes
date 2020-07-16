//
//  main.c
//  time
//
//  Created by Arsalan Iravani on 03.03.17.
//  Copyright © 2017 Arsalan Iravani. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[]) {
    time_t timep = time(0);
    struct tm * tmptr = localtime(&timep);
    
    printf("\n");
    
    printf("%ld\n", timep);
    printf("%s", ctime(&timep));
    printf("%s", asctime(tmptr));
    
    char buf[255];
    
//    strptime("2001-11-12 18:31:01", "%Y-%m-%d %H:%M:%S", tmptr);
    
    strptime(ctime(&timep), "%a %b %d %H:%M:%S %Y", tmptr);
    strftime(buf, sizeof(buf), "%d %b %Y / %H:%M", tmptr);
    puts(buf);
    exit(EXIT_SUCCESS);
    
    return 0;
}


