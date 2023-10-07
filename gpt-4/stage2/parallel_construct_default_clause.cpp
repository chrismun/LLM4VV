#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:parallel construct default clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int array_size = 100;
    float *a = (float*) malloc(array_size * sizeof(float));

    #pragma acc data copy(a[0:array_size])
    {
        #pragma acc parallel loop default(present)
        for(int i=0; i<array_size; i++) {
            a[i] = i * 1.0f;
        }
    }

    /* check results */
    for(int i=0; i<array_size; i++) {
        if(a[i] != i*1.0f) {
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