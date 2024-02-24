#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data from host to device
    #pragma acc data copyin(a) copyout(b)
    {
        // Use the host_data construct with an if clause
        #pragma acc host_data if(1)
        {
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1; // Return non-zero to indicate failure
        }
    }

    printf("Success!\n");
    return 0; // Return zero to indicate success
}