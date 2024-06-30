#include <unistd.h>
#include <sys/syscall.h>
#include <sys/signal.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
const int MAXBUF = 1024;
void handler1(int sig) {
    int olderrno = errno;
    pid_t pid;
    if ((pid = waitpid(-1, NULL, 0)) < 0) {
        write(1, "waitpid error\n", 15);
        _exit(1);
    }
    printf("handler reaped child: %d\n", pid);
    sleep(1);
    errno = olderrno;
}

void handler2(int sig) {
    int olderrno = errno;
    while ((waitpid(-1, NULL, 0)) > 0) {
        write(1, "handler reaped child\n", 22);
    }
    if (errno != ECHILD) {
        write(1, "waitpid error\n", 15);
        _exit(1);
    }
    sleep(1);
    errno = olderrno;
}

int main() {
    int i, n;
    char buf[MAXBUF];
    signal(SIGCHLD, handler1);

    for (int i = 0; i < 3; ++i) {
        if (fork() == 0) {
            printf("hello from child: %d\n", (int)getpid());
            exit(0);
        }
    }

    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0) {
        write(1, "read error\n", 12);
        exit(1);
    } 
    printf("parent processing\n");
    system("ps t");
    exit(0);
}