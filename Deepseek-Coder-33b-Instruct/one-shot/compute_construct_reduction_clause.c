#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int sum = 0;
    int sum_gpu = 0;
    int *data = (int*)malloc(N * sizeof(int));

    // Initialize data
    for(i = 0; i < N; i++) {
        data[i] = i + 1;
    }

    // Calculate sum on CPU
    for(i = 0; i < N; i++) {
        sum += data[i];
    }

    printf("CPU sum: %d\n", sum);

    // Calculate sum on GPU
    #pragma acc data copyin(data[0:N]) copy(sum_gpu)
    {
        #pragma acc parallel loop reduction(+:sum_gpu)
        for(i = 0; i < N; i++) {
            sum_gpu += data[i];
        }
    }

    printf("GPU sum: %d\n", sum_gpu);

    // Verify results
    if(sum == sum_gpu) {
        printf("Verification successful!\n");
    } else {
        printf("Verification failed!\n");
    }

    free(data);

    return 0;
}