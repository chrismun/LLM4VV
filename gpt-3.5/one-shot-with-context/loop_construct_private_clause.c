#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define SIZE 100

int main() {
    int a[SIZE];
    int b[SIZE];
    int c[SIZE];

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = i*2;
    }

    #pragma acc parallel loop copyin(b[0:SIZE], c[0:SIZE]) private(a)
    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i] + c[i];
    }

    // Check if computation is correct
    int success = 1;
    for (int i = 0; i < SIZE; i++) {
        if (a[i] != b[i] + c[i]) {
            success = 0;
            break;
        }
    }

    if (success) {
        printf("Computation is correct\n");
    } else {
        printf("Computation is incorrect\n");
    }

    return 0;
}