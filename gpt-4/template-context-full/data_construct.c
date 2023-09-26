#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1: data construct, V: 2.0-2.7*/
int test1() {
    int err = 0;
    int length = 5;
    float *a, *b;

    /* Allocate memory and initialize data */
    a = (float *)malloc(length * sizeof(float));
    b = (float *)malloc(length * sizeof(float));

    for (int i = 0; i < length; i++) {
        a[i] = i * 0.1;
        b[i] = 0.0;
    }

    /* Data construct ensuring data is copied to device memory and back */
    #pragma acc data copy(a[0:length]), copyout(b[0:length])
    {
        #pragma acc parallel loop
        for(int i = 0; i < length; i++) {
            b[i] = a[i] + 1;
        }
    }

    /* Check results */
    for(int i = 0; i < length; i++) {
        if(a[i]+1 != b[i]) {
            err = 1;
            break;
        }
    }

    /* Free allocated memory */
    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}