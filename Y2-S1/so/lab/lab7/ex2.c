#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>

int th_blocked, n;
pthread_mutex_t mtx;
sem_t sem;

void barrier_point() {
	pthread_mutex_lock(&mtx);
	++th_blocked;
	pthread_mutex_unlock(&mtx);
}

void *tfun(void *v) {
	int tid = *((int *) v);

	printf("%d reached the barrier\n", tid);

	barrier_point();

	if (th_blocked < n) {
		sem_wait(&sem);
	}
	
	if (th_blocked == n) {
		sem_post(&sem);
	}


	printf("%d passed the barrier\n", tid);
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Please set the number of threads\n");
	}

	n = atoi(argv[1]);
	pthread_t *th_arr = (pthread_t *) malloc(n * sizeof(pthread_t));

	if (pthread_mutex_init(&mtx, NULL)) {
		perror(NULL);
		return errno;
	}

	if (sem_init(&sem, 0, 0)) {
		perror(NULL);
		return errno;
	}

	int *num_arr = (int *) malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i) {
		pthread_t th;
		num_arr[i] = i;
		if (pthread_create(&th, NULL, tfun, &num_arr[i])) {
			perror(NULL);
			return errno;
		}

		th_arr[i - 1] = th;
	}

	for (int i = 0; i < n; ++i) {
		void *res;
		if (pthread_join(th_arr[i], &res)) {
			perror(NULL);
			return errno;
		}
	}

	if (pthread_mutex_destroy(&mtx)) {
		perror(NULL);
		return errno;
	}

	sem_destroy(&sem);

	free(th_arr);
	free(num_arr);
	return 0;
}