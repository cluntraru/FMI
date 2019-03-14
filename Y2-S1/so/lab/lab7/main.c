#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

const int kMaxThreads = 10;

int available_resources = 10;
pthread_mutex_t mtx;

int decrease_count(int count) {
	pthread_mutex_lock(&mtx);
	if (available_resources < count) {
		pthread_mutex_unlock(&mtx);
		return -1;
	}

	available_resources -= count;
	printf("Got %d resources, %d remaining\n", count, available_resources);
	pthread_mutex_unlock(&mtx);

	return 0;
}

int increase_count(int count) {
	pthread_mutex_lock(&mtx);
	available_resources += count;
	printf("Released %d resources, %d remaining\n", count, available_resources);
	pthread_mutex_unlock(&mtx);
	return 0;
}

void *use_resources(void *args) {
	int res_cnt = rand() % 5;
	decrease_count(res_cnt);
	increase_count(res_cnt);
 
	return NULL;
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		printf("Please set the number of threads\n");
	}

	int n = atoi(argv[1]);
	pthread_t *th_arr = (pthread_t *) malloc(n * sizeof(pthread_t));

	for (int i = 0; i < n; ++i) {
		pthread_t th;
		if (pthread_create(&th, NULL, use_resources, NULL)) {
			perror(NULL);
			return errno;
		}

		th_arr[i - 1] = th;
	}

	if (pthread_mutex_init(&mtx, NULL)) {
		perror(NULL);
		return errno;
	}

	for (int i = 0; i < n; ++i) {
		void *res;
		if (pthread_join(th_arr[i - 1], &res)) {
			perror(NULL);
			return errno;
		}
	}

	if (pthread_mutex_destroy(&mtx)) {
		perror(NULL);
		return errno;
	}

	return 0;
}