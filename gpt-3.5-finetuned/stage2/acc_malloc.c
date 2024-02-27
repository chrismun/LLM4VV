#include "acc_testsuite.h"
#ifndef T1
//T1:acc_malloc,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    unsigned int *a = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int *b = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int *c = (unsigned int *)malloc(n * sizeof(unsigned int));
    unsigned int *meanc = (unsigned int *)malloc(n * sizeof(unsigned int));

    // complete test here

    free(a);
    free(b);
    free(c);
    free(meanc);
    return err;
}

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