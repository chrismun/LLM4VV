#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,loop,V:2.7-3.3
int test1(){
    

    int defaultN = 1024*1024;
    int* a = (int *)malloc(defaultN * sizeof(int));
    int i;
    

    for(i = 0; i < defaultN; ++i){
        a[i] = 1;
    }

    #pragma acc kernels loop num_gangs(defaultN)
    for(i = 0; i < defaultN; ++i){
        a[i] += 2;
    }
    
    int errors = 0;
    
    for(i = 0; i < defaultN; ++i){
        if(a[i] != 3){
            errors += 1;
        }
    }

    return errors;
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