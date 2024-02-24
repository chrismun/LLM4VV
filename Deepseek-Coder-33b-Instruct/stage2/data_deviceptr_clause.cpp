#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], a_device[N];
    int i, err = 0;

    // Initialize the array on the host
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy the array to the device
    #pragma acc data copyin(a[:N]) copyout(a_device[:N])
    {
        // Modify the array on the device
        #pragma acc kernels
        for (i = 0; i < N; i++) {
            a_device[i] = a[i] * 2;
        }
    }

    // Compare the modified array with the original array
    for (i = 0; i < N; i++) {
        if (a_device[i] != a[i] * 2) {
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