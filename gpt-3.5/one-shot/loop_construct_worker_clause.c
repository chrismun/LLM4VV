#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define N 1000

void worker_code(int* array, int index) {
    int value = array[index];
    printf("Worker %d is processing value %d\n", index, value);
}

int main() {
    int* data = (int*)malloc(N * sizeof(int));

    // Initialize data array
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Execute loop construct with worker clause
    #pragma acc parallel loop worker(N) present(data[:N])
    for (int i = 0; i < N; i++) {
        worker_code(data, i);
    }

    free(data);

    return 0;