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
    #pragma acc parallel loop private(a)
    for (i = 0; i < N; i++) {
        a[i]++;
    }

    // Check the results
    int success = 1;
    for (i = 0; i < N; i++) {
        if (a[i] != i + 1) {
            success = 0;
            break;
        }
    }

    if (success) {
        printf("OpenACC implementation of private clause is correct.\n");
    } else {
        printf("OpenACC implementation of private clause is incorrect.\n");
    }

    return 0;
}