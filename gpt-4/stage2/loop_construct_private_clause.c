#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:loop construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int n = 10;
    int a[n], b[n], c[n], tmp;
    
    // Initialization of arrays
    for(int i=0; i<n; i++){
        a[i] = i;
        b[i] = i*2;
        c[i] = i*3;
    }

    // OpenACC parallel region
    #pragma acc parallel copy(a, b, c)
    {
        #pragma acc loop private(tmp)
        for(int i=0; i<n; i++){
            tmp = b[i] + c[i];
            a[i] = a[i] + tmp;
        }
    }

    // verification
    for(int i=0; i<n; i++){
        if(a[i] != i + (2*i + 3*i)){
            err = 1;
        }
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    int NUM_TEST_CALLS = 1;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}