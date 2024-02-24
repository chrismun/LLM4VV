#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

#ifndef T1
//T1:parallel construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(256 * sizeof(int));
    int *b = (int *)malloc(256 * sizeof(int));

    for (int x = 0; x < 256; ++x) {
        a[x] = rand() % 256;
        b[x] = 0;
    }

    #pragma acc parallel loop copy(a[0:256]) copyout(b[0:256])
    for (int x = 0; x < 256; ++x) {
        b[x] = a[x] * 2;
    }

    for (int x = 0; x < 256; ++x) {
        if (b[x] != a[x] * 2) {
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