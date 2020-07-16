#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void err_exit(int err, char *msg) {
    fprintf(stderr, "Error: %d, %s\n", err, msg);
    exit(1);
}

void * thr_fn1(void *arg) {
    printf("thread 1 returning\n");
    return((void *)1);
}

struct some_structure {
    int x, y;
};

void * thr_fn2(void *arg) {
    printf("thread 2 exiting\n");
    struct some_structure *s = malloc(sizeof(struct some_structure));
    s->x = 5;
    s->y = 6;
    pthread_exit((void *)s);
}

int main(void) {
    int         err;
    pthread_t   tid1, tid2;
    void        *tret;
    
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        err_exit(err, "can't create thread 1");
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        err_exit(err, "can't create thread 2");
    
    err = pthread_join(tid1, &tret);
    if (err != 0)
        err_exit(err, "can't join with thread 1");
    printf("thread 1 exit code %ld\n", (long)tret);
    
    err = pthread_join(tid2, &tret);
    
    if (err != 0)
        err_exit(err, "can't join with thread 2");
    printf("thread 2 exit code x: %d, y: %d\n",
           ((struct some_structure*)tret)->x,
           ((struct some_structure*)tret)->y);
    
    exit(0);
}
