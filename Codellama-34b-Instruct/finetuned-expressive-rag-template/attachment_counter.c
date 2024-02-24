#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c;
    int size = 1024;

    a = (int *)malloc(size * sizeof(int));
    b = (int *)malloc(size * sizeof(int));
    c = (int *)malloc(size * sizeof(int));

    for (int x = 0; x < size; ++x){
        a[x] = rand() % size;
        b[x] = rand() % size;
        c[x] = 0;
    }

    #pragma acc enter data copyin(a[0:size], b[0:size])
    #pragma acc enter data create(c[0:size])

    #pragma acc parallel present(a, b, c)
    {
        #pragma acc loop
        for (int x = 0; x < size; ++x){
            c[x] = a[x] + b[x];
        }
    }

    #pragma acc exit data copyout(c[0:size])

    for (int x = 0; x < size; ++x){
        if (c[x] != a[x] + b[x]){
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a, b, c)

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