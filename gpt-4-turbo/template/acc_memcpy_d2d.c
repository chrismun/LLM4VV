#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b;
    int size = 1024; // size of arrays
    srand(SEED);

    a = (int*) acc_malloc(size * sizeof(int));
    b = (int*) acc_malloc(size * sizeof(int));

    if (a == NULL || b == NULL) {
        fprintf(stderr, "acc_malloc failed.\n");
        exit(1);
    }

    // fill 'a' with random data
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
    }

    // copy data from 'a' to 'b' using acc_memcpy_d2d
    acc_memcpy_d2d(b, a, size * sizeof(int));

    // verify the copy
    for(int i = 0; i < size; ++i){
        if (a[i] != b[i]){
            err++;
            break;
        }
    }

    // cleanup
    acc_free(a);
    acc_free(b);

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