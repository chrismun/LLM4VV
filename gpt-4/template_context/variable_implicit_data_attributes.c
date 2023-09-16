#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"
#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int* a;
    int n = 10000;
    a = (int*) malloc(n*sizeof(int));

    for(int i = 0; i < n; i++) a[i] = i;

    #pragma acc parallel loop
    for(int i = 0; i < n; i++) a[i] += 1;

    for(int i = 0; i < n; i++){
        if(a[i] != i+1){
            err = 1;
            break;
        }
    }

    free(a);

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