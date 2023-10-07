#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <OpenACC/openacc.h>

#define N 1000

int main() {
    int i;
    float sum = 0.0, sum_parallel = 0.0;

    float arr[N];
    for (i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    #pragma acc parallel loop reduction(+:sum_parallel)
    for (i = 0; i < N; i++) {
        sum_parallel += arr[i];
    }

    for (i = 0; i < N; i++) {
        sum += arr[i];
    }

    if (fabs(sum - sum_parallel) < 1e-6) {
        printf("Reduction test passed!\n");
    } else {
        printf("Reduction test failed!\n");
    }

    return 0;