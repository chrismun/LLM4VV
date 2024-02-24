#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], i;

    // Initialize the array
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Use OpenACC to copy the array to the device
    #pragma acc data copy(a)
    {
        // Check if the array is present in device memory
        if (acc_is_present(a, N * sizeof(int))) {
            printf("Array 'a' is present in device memory.\n");
        } else {
            printf("Array 'a' is not present in device memory.\n");
        }
    }

    return 0;
}