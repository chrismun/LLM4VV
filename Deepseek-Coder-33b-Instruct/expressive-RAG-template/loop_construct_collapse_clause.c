#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define N 100

int main() {
    int i, j;
    int a[N][N];
    int err = 0;

    // Initialize the array
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = i + j;
        }
    }

    // Use OpenACC to collapse the two loops
    #pragma acc parallel loop collapse(2)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = a[i][j] * 2;
        }
    }

    // Check the result
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (a[i][j] != (i + j) * 2) {
                err = 1;
                break;
            }
        }
    }

    if (err) {
        printf("Test failed\n");
    } else {
        printf("Test passed\n");
    }

    return err;
}