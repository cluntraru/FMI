#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

void collatz(int n) {
    int prev_n = n;
    while (n != 1) {
        printf("%d ", n);
        if (n % 2 == 0) {
            n /= 2;
        }
        else {
            n = 3 * n + 1;
        }

        if (prev_n == n) {
            printf("\n%s\n", "Collatz is false!");
            return;
        }

        prev_n = n;
    }

    printf("1\n");
}

int main(int argc, char const *argv[]) {
    int new_pid = fork();
    int n = atoi(argv[1]);

    if (new_pid == 0) { // child process
        collatz(n);
        printf("Child %d finished\n", getpid());
    }
    else if (new_pid < 0) {
        printf("%s\n", "Process creation failed");
        return errno;
    }
    else { //parent process
        wait(NULL);
    }
    return 0;
}
