#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int i, sum = 0;
    int a[N];

    // Initialize the array
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Compute the sum of the array elements
    #pragma acc parallel loop reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("The sum is: %d\n", sum);

    return 0;
}