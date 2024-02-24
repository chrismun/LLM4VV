#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int sum = 0;
    int expected_sum = N * (N - 1) / 2;

    #pragma acc parallel loop reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += i;
    }

    if (sum == expected_sum) {
        printf("Reduction clause implemented correctly.\n");
    } else {
        printf("Reduction clause not implemented correctly.\n");
    }

    return 0;
}