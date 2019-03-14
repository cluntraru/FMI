#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *reverse(void *args) {
    char *str = (char *) args;

    int len = strlen(str);
    char *str_res = (char *) malloc((len + 1) * sizeof(char));
    
    // Also copy \0
    for (int i = len - 1; i >= 0; --i) {
        str_res[len - i - 1] = str[i];
    }

    for (int i = 0; i < len; ++i) {
        str[i] = str_res[i];
    }

    return str_res;
}

int main(int argc, char *argv[]) {
    int len = strlen(argv[1]);
    char *str = malloc((len + 1) * sizeof(char));
    memcpy(str, argv[1], len);

    pthread_t t_id;
    if (pthread_create(&t_id, NULL, reverse, argv[1]) != 0) {
        printf("Thread creation failed!");
        return 0;
    }

    void *str_res;
    if (pthread_join(t_id, &str_res) != 0) {
        printf("Thread join failed!");
        return 0;
    }

    printf("%s\n", (char *) str_res);
    free(str);
    free(str_res);
    return 0;
}