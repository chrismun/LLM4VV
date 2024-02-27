#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1:reference_counters, V:2.7-3.3
int test1(){
    int err = 0;
    float *a, *d_a;
    int n = 100;
    a = (float*)malloc(n * sizeof(float));

    // Enter data region and create
    #pragma acc enter data create(a[0:n])
    d_a = acc_deviceptr(a);
    if (d_a == NULL) {
        fprintf(stderr, "Error: acc_deviceptr returned NULL\n");
        err = 1;
    }

    // Check if data is considered present
    if (!acc_is_present(a, n * sizeof(float))) {
        fprintf(stderr, "Error: data is not present on the device as expected\n");
        err = 1;
    }

    // Exit data region
    #pragma acc exit data delete(a[0:n])

    // Try to access device pointer which should not be accessible now, using acc_is_present to infer the result
    if (acc_is_present(a, n * sizeof(float))) {
        fprintf(stderr, "Error: data is still present on the device when it should not be\n");
        err = 1;
    }

    free(a);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    #ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){ // Assuming a single call suffices for our simple test
        failed += test1();
    }
    if (failed != 0){
        failcode += 1 << 0;
    }
    #endif
    return failcode;
}