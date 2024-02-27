#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    const int n = 1024; // Size of array
    const int num_gangs = 4; // Number of gangs
    const int vector_length = 256; // Assuming each gang will work on 256 elements
    float *a = (float *)malloc(n * sizeof(float));
    float *result = (float *)malloc(sizeof(float));
    result[0] = 0.0f;
    float expected_result = 0.0f;

    // Initializing array and calculating expected result
    for (int i = 0; i < n; ++i) {
        a[i] = 1.0f; // Simplified computation: summing 1's
        expected_result += a[i];
    }

    #pragma acc data copyin(a[0:n]) copyout(result[0:1])
    {
        #pragma acc parallel num_gangs(num_gangs) vector_length(vector_length) reduction(+:result[0])
        {
            #pragma acc loop reduction(+:result[0])
            for(int i = 0; i < n; ++i){
                result[0] += a[i];
            }
        }
    }

    if (fabs(expected_result - result[0]) > 1e-5) {
        err += 1;
    }

    free(a);
    free(result);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test1();
    if (failed != 0){
        failcode += (1 << 0);
        printf("Test1 failed.\n");
    } else {
        printf("Test1 passed.\n");
    }
#endif

    return failcode;
}