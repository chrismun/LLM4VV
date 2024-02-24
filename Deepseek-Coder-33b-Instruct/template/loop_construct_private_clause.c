#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int sum = 0;
    int data[N];
    int sum_gpu = 0;

    // Initialize data array
    for (i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    // Compute sum on CPU
    for (i = 0; i < N; i++) {
        sum += data[i];
    }

    printf("CPU sum: %d\n", sum);

    // Compute sum on GPU
    #pragma acc parallel loop copy(data[0:N]) copyout(sum_gpu)
    for (i = 0; i < N; i++) {
        sum_gpu += data[i];
    }

    printf("GPU sum: %d\n", sum_gpu);

    // Verify results
    if (sum == sum_gpu) {
        printf("Verification successful!\n");
    } else {
        printf("Verification failed!\n");
    }

    return 0;
}