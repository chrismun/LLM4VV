#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef T1
// T1: async, data, kernels, V:1.0-2.7
int test_acc_async(){
    int err = 0;
    const int n = 1024;
    srand(2023); // Seed for reproducibility
    float * a = (float *)malloc(n * sizeof(float));
    float * b = (float *)malloc(n * sizeof(float));

    for (int i = 0; i < n; ++i){
        a[i] = rand() / (float)(RAND_MAX);
        b[i] = 0.0f;
    }

    // Using async clause
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels async
        {
            for(int i = 0; i < n; ++i){
                b[i] = a[i];
            }
        }
        // wait for the completion of the previous async region
        #pragma acc wait
    }

    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - a[i]) > 1e-5){
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

    // Test for async
    failed = test_acc_async();
    if (failed != 0){
        printf("ASYNC TEST FAILED with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("ASYNC TEST PASSED.\n");
    }

    return failcode;
}