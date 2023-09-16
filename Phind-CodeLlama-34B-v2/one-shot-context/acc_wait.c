#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>

#define N 100000000
#define TRIALS 10

void vector_add(int *a, int *b, int *c, int n) {
    #pragma acc kernels
    {
        #pragma acc loop
        for (int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }
}

int main() {
    int *a, *b, *c;
    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));
    c = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    double total_time_with_wait = 0.0;
    double total_time_without_wait = 0.0;

    for (int trial = 0; trial < TRIALS; trial++) {
        clock_t start_time = clock();
        vector_add(a, b, c, N);
        clock_t end_time = clock();
        total_time_without_wait += (double)(end_time - start_time) / CLOCKS_PER_SEC;

        start_time = clock();
        acc_wait(1);
        vector_add(a, b, c, N);
        acc_wait(1);
        end_time = clock();
        total_time_with_wait += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }

    printf("Average time without acc_wait: %lf\n", total_time_without_wait / TRIALS);
    printf("Average time with acc_wait: %lf\n", total_time_with_wait / TRIALS);

    if (total_time_with_wait > total_time_without_wait) {
        printf("acc_wait is working correctly.\n");
    } else {
        printf("acc_wait is not working correctly.\n");
    }

    free(a);
    free(b);
    free(c);

    return 0;
}