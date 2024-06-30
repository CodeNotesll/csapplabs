#include <signal.h>
#include <sys/elf.h>
#include <syscall.h>

int main() {
    sigset_t mask;
    sigfillset(&mask);
}