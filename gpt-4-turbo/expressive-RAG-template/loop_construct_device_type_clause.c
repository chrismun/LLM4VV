#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#ifndef T1
//T1:loop construct, device_type clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Fixed seed for reproducibility

    const int size = 1000;
    float *a = (float*)malloc(size * sizeof(float));

    // Initialize array
    for (int i = 0; i < size; i++) {
        a[i] = i * 1.0f;
    }

    // Using OpenACC parallel loop construct with device_type clause
    #pragma acc parallel loop device_type(acc_device_default)
    for (int i = 0; i < size; ++i) {
        a[i] = a[i] * 2.0f;
    }

    // Verify the multiplication was done correctly
    for (int i = 0; i < size; ++i) {
        if (a[i] != i * 2.0f) {
            err++;
        }
    }

    free(a);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 10; ++x){ // Assuming NUM_TEST_CALLS is replaced by a fixed number for simplicity
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}