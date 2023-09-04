#include "acc_testsuite.h"
#ifndef T3
//T3:parallel,loop,collapse,V:2.0-2.7
int test3(int *a, int *b, int *c, int loopCount){
    int err = 0;

    for (int x = 0; x < loopCount; ++x){
        a[x] = x;
        b[x] = x;
        c[x] = 0;
    }

    #pragma acc parallel loop collapse(2) present(a[0:loopCount], b[0:loopCount], c[0:loopCount])
    for (int x = 0; x < loopCount; ++x){
        for (int y = 0; y < loopCount; ++y){
            c[x] += a[x] * b[y];
        }
    }

    for (int x = 0; x < loopCount; ++x){
        if (c[x] != x*(x*loopCount)){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T3
    int loopCount = 512;
    int *a = (int *)malloc(loopCount * sizeof(int));
    int *b = (int *)malloc(loopCount * sizeof(int));
    int *c = (int *)malloc(loopCount * sizeof(int));

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3(a, b, c, loopCount);
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }

    free(a);
    free(b);
    free(c);

#endif
    return failcode;
}