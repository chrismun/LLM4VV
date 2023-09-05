#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#ifndef N
#define N 10000000
#endif

#ifndef CHUNK_SIZE
#define CHUNK_SIZE 1000
#endif

int main() {
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    // Initialize the arrays
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = 0;
    }

    // Compute the sum of the arrays using OpenACC directives
    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        int start = tid * (N / 2);
        int end = (tid + 1) * (N / 2);

        #pragma acc parallel loop present(a[start:end], b[start:end])
        for (int i = start; i < end; ++i) {
            b[i] = a[i] + a[i];
        }
    }

    // Verify the result
    int error = 0;
    for (int i = 0; i < N; ++i) {
        if (b[i] != a[i] * 2) {
            printf("ERROR: Incorrect result\n");
            error = 1;
            break;
        }
    }

    if (!error) {
        printf("SUCCESS: Result is correct\n");
    }

    // Shutdown the OpenACC runtime and clean up
    #pragma acc shutdown

    free(a);
    free(b);

    return 0;