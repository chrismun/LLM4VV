#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int test1(){
    int err = 0;
    int a[N], b[N], c[N];
    int *dev_a, *dev_b, *dev_c;

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Allocate memory on device
    dev_a = (int*)acc_malloc(N * sizeof(int));
    dev_b = (int*)acc_malloc(N * sizeof(int));
    dev_c = (int*)acc_malloc(N * sizeof(int));

    // Copy data to device
    acc_memcpy_to_device(dev_a, a, N * sizeof(int));
    acc_memcpy_to_device(dev_b, b, N * sizeof(int));

    // Perform vector addition
    #pragma acc parallel loop vector_length(128)
    for (int i = 0; i < N; i++) {
        dev_c[i] = dev_a[i] + dev_b[i];
    }

    // Copy data back to host
    acc_memcpy_from_device(c, dev_c, N * sizeof(int));

    // Verify result
    for (int i = 0; i < N; i++) {
        if (c[i] != 2 * i) {
            err = 1;
            break;
        }
    }

    // Free memory
    acc_free(dev_a);
    acc_free(dev_b);
    acc_free(dev_c);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}