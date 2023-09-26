#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: acc free, V: 2.7-3.3
int test1(){
    int err = 0;
    const int n = 100;

    int* a = (int*)malloc(n * sizeof(int));
    if (a == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    int* b = (int*)malloc(n * sizeof(int));
    if (b == NULL) {
        printf("Memory allocation failed\n");
        free(a);
        return 1;
    }

    #pragma acc data copyin(a[:n]) copyout(b[:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            b[i] = a[i] + 1;
        }
    }

    #pragma acc data copyin(a[:n])
    {
        // Use the allocated memory without a data construct
        for (int i = 0; i < n; ++i){
            a[i] = i;
        }
    }

    #pragma acc exit data copyout(b[:n])
    for (int i = 0; i < n; ++i){
        if (b[i] != i + 1) {
            err = 1;
            break;
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