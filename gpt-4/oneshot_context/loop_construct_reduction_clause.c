#include <stdio.h>
#include <stdlib.h>

// Kernel to perform reduction on the device using OpenACC
#pragma acc routine seq
void sum(int* a, int* b, int n) {
    int sum = 0;
    #pragma acc loop reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        sum += a[i]*b[i];
    }
    return sum;
}

int main(int argc, char** argv) {
    // Array size
    int n = 1000;

    // Host arrays
    int* h_a = (int*)malloc(n*sizeof(int));
    int* h_b = (int*)malloc(n*sizeof(int));

    // Initialize host arrays
    for(int i = 0; i < n; ++i) {
        h_a[i] = i;
        h_b[i] = i;
    }

    // Device sum
    int h_sum = 0;

    // Allocate device memory
    #pragma acc data copyin(h_a[0:n], h_b[0:n]) copyout(h_sum)
    {
        // Call the kernel
        sum(h_a, h_b, n);

        // Copy result back to host
        #pragma acc update host(h_sum)
    }

    // Compute sum on host to check device computation
    int h_sum_check = 0;
    for (int i = 0; i < n; ++i) {
        h_sum_check += h_a[i]*h_b[i];
    }

    // Check result
    if (h_sum_check != h_sum) {
        printf("Check failed: host sum (%d) != device sum (%d)\n", h_sum_check, h_sum);
        exit(EXIT_FAILURE);
    }

    printf("Check passed.\n");

    return 0;