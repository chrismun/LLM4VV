#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize the array on the host
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy the array to the device
    #pragma acc data copyin(a) copyout(b)
    {
        // Copy the array from the device to the host
        #pragma acc update host(b)

        // Modify the array on the host
        for (i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }

        // Copy the array from the host to the device
        #pragma acc update device(b)

        // Delete the array from the device
        #pragma acc exit data delete(b)
    }

    // Check the result
    for (i = 0; i < N; i++) {
        if (b[i] != i * 2) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], i * 2);
            return 1;
        }
    }

    printf("Success!\n");
    return 0;
}