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

    // Copy data to device
    #pragma acc data copyin(a[:N]) copyout(b[:N])
    {
        // Copy data from device to host if present
        #pragma acc host_data if_present(a[:N])
        {
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check if data was copied correctly
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: Data not copied correctly\n");
            return 1;
        }
    }

    printf("Success: Data copied correctly\n");
    return 0;
}