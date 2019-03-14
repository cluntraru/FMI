#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int main() {
    int new_pid = fork();
    if (new_pid == 0) { // this is the child process
        printf("My PID = %d, Child PID = %d\n", getppid(), getpid());
        char *const argv[] = {"ls", ".", NULL};
        execve("/bin/ls", argv, NULL);
    }
    else if (new_pid < 0) {
        printf("%s", "Process creation failed");
        return errno;
    }
    else { // parent process
        wait(NULL);
    }
    return 0;
}
