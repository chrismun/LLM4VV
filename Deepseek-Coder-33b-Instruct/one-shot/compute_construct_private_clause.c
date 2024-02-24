#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N];
    int i;

    // Initialize the array
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc parallel loop private(i)
    for (i = 0; i < N; i++) {
        a[i] += 1;
    }

    // Verify the results
    for (i = 0; i < N; i++) {
        if (a[i] != i + 1) {
            printf("Error at index %d: expected %d, got %d\n", i, i + 1, a[i]);
            return 1;
        }
    }

    printf("All tests passed.\n");
    return 0;
}