#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s) {
    pid_t       pid;
    pthread_t   tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
      (unsigned long)tid, (unsigned long)tid);
}

struct data {
    
};

void * thr_fn() {
    printids("new thread: ");
    return((void *)0);
}

int main() {
    
    data* ptr;
    
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, data);
    if (err != 0) {
        fprintf(stderr, "Error: %d | can't create thread", err);
        exit(1);
    }
    
    printids("main thread:");
    sleep(1);
    exit(0);
}
