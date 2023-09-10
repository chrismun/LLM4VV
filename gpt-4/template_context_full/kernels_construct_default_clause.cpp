#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:kernels construct default clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int arraySize = 50;
    int a[arraySize], b[arraySize], c[arraySize];

    // Initialize arrays
    for(int i = 0; i < arraySize; ++i) {
        a[i] = rand() % 50;
        b[i] = rand() % 50;
        c[i] = 0;
    }

    // Default clause
    #pragma acc kernels default(none) copy(a, b, c)
    {
        for(int i = 0; i < arraySize; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    // Check the results
    for(int i = 0; i < arraySize; ++i) {
        if(c[i] != a[i] + b[i]){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}