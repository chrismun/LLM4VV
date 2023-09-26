#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc memcpy device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c;
    int size = 1024;
    a = (int *)malloc(size * sizeof(int));
    b = (int *)malloc(size * sizeof(int));
    c = (int *)acc_malloc(size * sizeof(int));

    for (int x = 0; x < size; ++x) {
        a[x] = rand() % size;
        b[x] = 0;
    }

    acc_memcpy_device(c, a, size * sizeof(int));
    acc_memcpy_device(b, c, size * sizeof(int));

    for (int x = 0; x < size; ++x) {
        if (a[x] != b[x]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    acc_free(c);

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