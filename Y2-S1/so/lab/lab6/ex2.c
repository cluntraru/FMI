#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct mat_pos_args {
    int len;
    int *row_mat_a;
    int *col_mat_b;
};

void print_matrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n-------------------------\n");
}

void *get_mat_pos(void *args) {
    struct mat_pos_args *mat_args = args;
    int *val = (int *) malloc(sizeof(int));
    for (int i = 0; i < mat_args->len; ++i) {
        *val += mat_args->row_mat_a[i] * mat_args->col_mat_b[i];
    }

    free(mat_args);
    return (void *) val;
}

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int **alloc_mat(int rows, int cols) {
    int *block = malloc(rows * cols * sizeof(int));
    int **mat = malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; ++i) {
        mat[i] = block + i * cols;
    }

    return mat;
}

void free_mat(int **mat) {
    free(mat[0]);
    free(mat);
}

int **transp_mat(int **mat, int rows, int cols) {
    int **transp = alloc_mat(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transp[j][i] = mat[i][j];
        }
    }

    return transp;
}

int **mult_matrix(int **mat_a, int **mat_b, int m, int p, int n) {
    int **transp_b = transp_mat(mat_b, p, n);
    int **ans = alloc_mat(m, n);

    pthread_t *t_ids = malloc(m * n * sizeof(pthread_t));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            struct mat_pos_args *mat_args = (struct mat_pos_args *) malloc(sizeof(struct mat_pos_args));
            mat_args->len = p;
            mat_args->row_mat_a = mat_a[i];
            mat_args->col_mat_b = transp_b[j];

            pthread_t t_id;
            pthread_create(&t_id, NULL, get_mat_pos, (void *) mat_args);

            int curr_idx = i * n + j;
            t_ids[curr_idx] = t_id;
        }
    }

    printf("\n");

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int curr_idx = i * n + j;
            void *val;
            pthread_join(t_ids[curr_idx], &val);
            ans[i][j] = *((int *) val);
            free(val);
        }
    }

    free_mat(transp_b);
    free(t_ids);
    return ans;
}

int main(int argc, char *argv[]) {
    int m, n, p;
    m = atoi(argv[1]);
    p = atoi(argv[2]);
    n = atoi(argv[3]);

    int **mat_a = alloc_mat(m, p);
    int **mat_b = alloc_mat(p, n);

    int argv_cnt = 4;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            mat_a[i][j] = atoi(argv[argv_cnt]);
            ++argv_cnt;
        }
    }

    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < n; ++j) {
            mat_b[i][j] = atoi(argv[argv_cnt]);
            ++argv_cnt;
        }
    }

    print_matrix(mat_a, m, p);
    print_matrix(mat_b, p, n);

    int **ans = mult_matrix(mat_a, mat_b, m, p, n);
    print_matrix(ans, m, n);

    free(mat_a);
    free(mat_b);
    free(ans);
    return 0;
}

// Input: 3 5 4 12 4 2 231 11 33 33 33 33 33 12 213 66 2 4 23 213 89 33 11 324 2 66 132 8 6 15 55 1 6 99 1 22 1 7
// Output: 13300 4341 2485 23636 
//         7326 18744 3432 7260 
//         11445 72186 1906 15670