/*
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

struct sigaction act;

void sighandler(int signum, siginfo_t *info, void *ptr) {
    printf("Received signal %d\n", signum);
    printf("Signal originates from process %lu\n", (unsigned long)info->si_pid);
}

int main() {
    printf("I am %lu\n", (unsigned long)getpid());
    
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = sighandler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGTERM, &act, NULL);
    
    // Waiting for CTRL+C...
    
    sleep(100);
    return 0;
}
*/

/* This program illustrates the different behaviour between a system call
 * that is restarted after being interrupted and one where the call is
 * interrupted and we need to manually check this condition.
 *
 * This code example is derived from:
 * http://www.win.tue.nl/~aeb/linux/lk/lk-4.html
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int restarted = 0;

void
sig_handler(int signo) {
    write(STDOUT_FILENO, "interrupted\n", 12);
    restarted = 1;
}

int
main(void) {
    struct sigaction sa;
    ssize_t n;
    char c;
    
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        fprintf(stderr, "Unable to establish signal handler for SIGINT: %s\n",
                strerror(errno));
        exit(1);
        /* NOTREACHED */
    }
    
    /* Ensure interrupted system calls are restarted rather than
     * setting errno to EINTR. */
    sa.sa_flags = SA_RESTART;
    
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        fprintf(stderr, "Unable to establish signal handler for SIGQUIT: %s\n",
                strerror(errno));
        exit(1);
    }

    if ((n = read(STDIN_FILENO, &c, 1)) < 0) {
        if (errno == EINTR) {
            printf("\nread call was interrupted\n");
        }
    } else if (restarted) {
        printf("\nread call was restarted\n");
    }
    
    printf("|%c|\n", c);
    return 0;
}
