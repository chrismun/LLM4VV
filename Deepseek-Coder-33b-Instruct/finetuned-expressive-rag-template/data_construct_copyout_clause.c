#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i, err = 0;

    // Initialize the array
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy the array to the device
    #pragma acc data copyin(a) copyout(b)
    {
        // Copy the array from the device to the host
        #pragma acc parallel loop copyout(b)
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Check if the arrays are the same
    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            err++;
        }
    }

    // Print the result
    if (err == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return err;
}