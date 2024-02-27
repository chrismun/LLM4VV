#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#ifndef T1
//T1:runtime,V:1.0-3.1
int test_init(){
    int err = 0;
    const int n = 1024;
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));

    // Initialize data
    for (int i = 0; i < n; ++i){
        a[i] = (float)i;
        b[i] = 0.0f;
    }

    // Explicitly initialize OpenACC runtime system
    acc_init(acc_device_default);

    // Perform copy operation
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            b[i] = a[i];
        }
    }

    // Verify the copying operation
    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - a[i]) > 1e-5){
            err += 1;
        }
    }

    // Shutdown OpenACC runtime system
    acc_shutdown(acc_device_default);

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;

    failed = test_init();
    if (failed != 0){
        failcode = 1;
    }

    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return failcode;
}