#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

const int kCntForCollatz = 250;
//const int kSpaceForCollatz = kCntForCollatz * 32;
const int kCollatzFalse = -2;
const int kCollatzNoSpace = -1;

const char kShmName[] = "collatz_shm";

void collatz(int *sh_arr, int n) {
    int prev_n = n;
    int print_cnt = 0;
    while (n != 1 && print_cnt < kCntForCollatz - 1) {
        sh_arr[print_cnt + 1] = n;
        if (n % 2 == 0) {
            n /= 2;
        }
        else {
            n = 3 * n + 1;
        }

        if (prev_n == n) {
            sh_arr[0] = kCollatzFalse;
            return;
        }

	    prev_n = n;
        ++print_cnt;
    }
    if (print_cnt == kCntForCollatz - 1) {
        sh_arr[0] = kCollatzNoSpace;
        return;
    }

    sh_arr[print_cnt] = 1;
    sh_arr[0] = print_cnt;
}

int make_sh_mem(int argc) {

    int shm_fd = shm_open(kShmName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) {
        return -1;
    }

    if (ftruncate(shm_fd, argc * sysconf(_SC_PAGESIZE) * sizeof(int)) == -1) {
        shm_unlink(kShmName);
        return -1;
    }

// DELETE
// int page_size = sysconf(_SC_PAGESIZE);
//     int *sh_arr = mmap(0, page_size * argc, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
//     if (sh_arr == MAP_FAILED) {
//         return -1;
//     }
//
//     for (int i = 0; i < page_size * argc / sizeof(int); ++i) {
//         printf("%d ", i);
//         if (sh_arr[i]) {
//             int a;
//             a = 0;
//         }
//     }
// DELETE

    return shm_fd;
}

void free_sh_mem() {
    shm_unlink(kShmName);
}

int print_sh_mem(int shm_fd, int argc) {
    int page_size = sysconf(_SC_PAGESIZE);
    int *sh_arr = mmap(0, page_size * argc, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sh_arr == MAP_FAILED) {
        return -1;
    }

    // for (int i = 0; i < page_size * argc / sizeof(int); ++i) {
    //     printf("%d ", sh_arr[i]);
    //     if (sh_arr[i]) {
    //       printf("%s %d\n", "HERE", i);
    //     }
    // }

    for (int i = 0; i < argc; ++i) {
      	int st_idx = i * page_size / 4;
        int cnt = sh_arr[st_idx];
      	for (int j = st_idx + 1; j <= st_idx + cnt; ++j) {
              printf("%d ", sh_arr[j]);
      	}

      	printf("\n");
    }

    if (munmap(sh_arr, page_size * argc) == -1) {
       return -1;
    }

    return 0;
}

int execute_child_process(int shm_fd, int child_idx, int n) {
    int page_size = sysconf(_SC_PAGESIZE);
    int *sh_arr = mmap(0, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd,
                       child_idx * page_size);

    if (sh_arr == MAP_FAILED) {
        return -1;
    }

    collatz(sh_arr, n);
    if (munmap(sh_arr, page_size) == -1) {
        return -1;
    }

    return 0;
}

void add_pid(int *pid_arr, int *pid_cnt, int pid) {
    pid_arr[*pid_cnt] = pid;
    ++(*pid_cnt);
}

int main(int argc, char *argv[]) {
    int shm_fd = make_sh_mem(argc - 1);
    if (shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    int *input = (int *) malloc(argc);
    for (int i = 1; i < argc; ++i) {
        input[i - 1] = atoi(argv[i]);
    }

    --argc;

    int *pid_arr = (int *) malloc(argc);
    int pid_cnt = 0;
    for (int i = 0; i < argc; ++i) {
        int new_pid = fork();
        if (new_pid == 0) {
            // child process
            if (execute_child_process(shm_fd, i, input[i]) == -1) {
                perror(NULL);
                return errno;
            }

            printf("Child process #%d with parent process #%d exited\n", getpid(), getppid());
            // child process end
            return 0;
        }
        else if (new_pid < 0) {
            printf("Child process failed to create\n");
            perror(NULL);
            return errno;
        }
        else {
            // parent process
            add_pid(pid_arr, &pid_cnt, new_pid);
        }
    }

    for (int i = 0; i < pid_cnt; ++i) {
        waitpid(pid_arr[i], NULL, 0);
    }

    print_sh_mem(shm_fd, argc);

    free_sh_mem();
    free(input);
    free(pid_arr);
    return 0;
}
