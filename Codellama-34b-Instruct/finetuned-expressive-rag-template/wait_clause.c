#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, i, j, async1, async2;
    int num_devices = acc_get_num_devices(acc_device_nvidia);

    if (num_devices == 0) {
        acc_set_device_num(acc_device_host);
    } else {
        acc_set_device_num(acc_device_nvidia, 0);
    }

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; ++i){
        a[i] = rand() % n;
        b[i] = rand() % n;
        c[i] = 0;
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(1)
        {
            #pragma acc loop
            for (i = 0; i < n; ++i){
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(2)
        {
            #pragma acc loop
            for (i = 0; i < n; ++i){
                c[i] = a[i] - b[i];
            }
        }

        #pragma acc wait(1)
        #pragma acc wait(2)
    }

    for (i = 0; i < n; ++i){
        if (c[i] != a[i] - b[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
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