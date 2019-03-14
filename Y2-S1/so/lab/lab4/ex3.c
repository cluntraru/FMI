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

void add_pid(int pid, int *pid_arr, int *pid_cnt) {
    pid_arr[*pid_cnt] = pid;
    ++(*pid_cnt);
}

int main(int argc, char const *argv[]) {
    int *pid_arr = (int *) malloc((argc - 1) * sizeof(int));
    int pid_cnt = 0;

    int parent_pid = getpid();

    for (int i = 1; i < argc; ++i) {
        int n = atoi(argv[i]);
        int new_pid = fork();
        if (new_pid == 0) { // child process
            collatz(n);
            break;
        }
        else if (new_pid < 0) { // Process creation failed
            return errno;
        }
        else { // parent process
            printf("Child process %d created\n", new_pid);
            add_pid(new_pid, pid_arr, &pid_cnt);
        }
    }

    if (getpid() == parent_pid) { // parent process needs to wait for all child processes
        for (int i = 0; i < pid_cnt; ++i) {
            waitpid(pid_arr[i], NULL, 0);
            printf("Child process %d exited\n", pid_arr[i]);
        }
    }
    return 0;
}
