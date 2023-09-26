#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:data construct copy clause,test:copy,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int length = 1024;
    int *a_host = (int*)malloc(length*sizeof(int));
    int *b_host = (int*)malloc(length*sizeof(int));

    for(int i=0; i<length; i++) {
        a_host[i] = (int)rand();
    }

#pragma acc data copy(a_host[0:length])
    {
#pragma acc kernels
        for(int i=0; i<length; i++) {
            a_host[i] = a_host[i] * 2;
        }
    }

    for(int i=0; i<length; i++) {
        if(a_host[i] != b_host[i]*2) {
            err = 1;
        }
    }

    free(a_host);
    free(b_host);
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