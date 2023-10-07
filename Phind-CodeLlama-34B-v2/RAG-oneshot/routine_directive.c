#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

void saxpy(float a, float *x, float *y, int n) {
    #pragma acc routine seq
    {
        #pragma acc loop vector
        for (int i = 0; i < n; i++) {
            y[i] = a * x[i] + y[i];
        }
    }
}

int main() {
    float *x = (float *)malloc(N * sizeof(float));
    float *y = (float *)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
    }

    saxpy(2.0, x, y, N);

    for (int i = 0; i < N; i++) {
        if (y[i] != i * 4) {
            printf("Test failed\n");
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}