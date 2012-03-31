#include <stdio.h>

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

	int *data_left = data;
	int len_left = pivot_pos;
	quick_sort(data_left, len_left);

	int *data_right = data + len_left + 1;
	int len_right = len - len_left - 1;
	quick_sort(data_right, len_right);
}

int main(int argc, char *argv[]) {
	int data[] = {38, 27, 43, 3, 9, 82, 10};
	const int count = sizeof(data) / sizeof(int);

	quick_sort(data, count);

	for (int i=0; i < count; ++i) {
		printf("%d ", data[i]);
	}
	printf("\n");

	return 0;
}
