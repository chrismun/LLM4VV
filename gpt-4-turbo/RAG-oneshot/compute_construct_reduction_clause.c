#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100000
#define PRECISION 0.001

double sequential_sum(double* array, int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

double parallel_sum(double* array, int n) {
    double sum = 0;
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    double* array = (double*)malloc(N * sizeof(double));
    for(int i = 0; i < N; i++) {
        // Initialize array with random numbers
        array[i] = (double)rand() / RAND_MAX;
    }

    double seq_sum = sequential_sum(array, N);
    double par_sum = parallel_sum(array, N);

    if (fabs(seq_sum - par_sum) < PRECISION) {
        printf("Test PASSED: Sequential sum %.6f matches Parallel sum %.6f\n", seq_sum, par_sum);
        free(array);
        return 0;
    } else {
        printf("Test FAILED: Sequential sum %.6f does NOT match Parallel sum %.6f\n", seq_sum, par_sum);
        free(array);
        return 1;
    }
}