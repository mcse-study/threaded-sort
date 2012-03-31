#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int do_pivot(int *data, int len) {
	int pivot = data[0];

	int l = 1, r = len-1;
	while (1) {
		for ( ; data[l] < pivot; ++l)
			;
		for ( ; pivot < data[r]; --r)
			;
		if (r <= l) {
			break;
		}

		int temp = data[l];
		data[l] = data[r];
		data[r] = temp;
	}

	data[0] = data[r];
	data[r] = pivot;

	return r;
}

typedef struct {
	int *data;
	int len;
} array_t;

void quick_sort(int *data, int len);

void *quick_sort_thread_wrapper(void *thread_arg) {
	array_t *pArray = (array_t *) thread_arg;

	int *data = pArray->data;
	int len = pArray->len;

	quick_sort(data, len);
	free(pArray);

	pthread_exit(NULL);
}

void create_quick_sort_thread(pthread_t *thread, int *data, int len) {
	array_t *pArray = malloc(sizeof(array_t));
	pArray->data = data;
	pArray->len = len;

	pthread_create(thread, NULL, quick_sort_thread_wrapper, (void *) pArray);
}

void quick_sort(int *data, int len) {
	switch (len) {
	case 2:
		if (data[0] > data[1]) {
			int temp = data[0];
			data[0] = data[1];
			data[1] = temp;
		}
	case 1:
	case 0:
		return;
	}

	int pivot_pos = do_pivot(data, len);

	pthread_t left_thread;
	pthread_t right_thread;

	create_quick_sort_thread(&left_thread, data, pivot_pos);
	pthread_join(left_thread, NULL);

	create_quick_sort_thread(&right_thread, data + pivot_pos + 1, len - pivot_pos - 1);
	pthread_join(right_thread, NULL);
}

int main(int argc, char *argv[]) {
	int data[] = {38, 27, 43, 3, 9, 82, 10};
	const int count = sizeof(data) / sizeof(int);

	quick_sort(data, count);

	for (int i=0; i < count; ++i) {
		printf("%d ", data[i]);
	}
	printf("\n");

	pthread_exit(NULL);

	return 0;
}
