#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    // Initialize array a
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    #pragma acc data copyin(a[0:N])
    {
        // Perform some computation on array a
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            a[i] += 1;
        }

        // Copy back data from the device to host
        #pragma acc data copyout(b[0:N])
        {
            // Copy array a to array b
            #pragma acc parallel loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Verify that array b contains the updated data from array a
    int success = 1;
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            success = 0;
            break;
        }
    }

    if (success) {
        printf("Data copied successfully\n");
    } else {
        printf("Data copy failed\n");
    }

    // Clean up memory
    free(a);
    free(b);

    return 0;
}