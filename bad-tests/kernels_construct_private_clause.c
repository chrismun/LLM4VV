#include "acc_testsuite.h"

#ifndef T1
/*T1:kernels construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int numGangs = 64;
    int vectorLength = 32;
    int * a = (int *)malloc(numGangs * vectorLength * sizeof(int));
    int * b = (int *)malloc(numGangs * vectorLength * sizeof(int));
    
    for (int x = 0; x < numGangs * vectorLength; ++x){
        a[x] = rand() / (float)RAND_MAX * 100;
        b[x] = 0;
    }
    
    #pragma acc data copy(a[0:numGangs*vectorLength], b[0:numGangs*vectorLength])
    #pragma acc kernels
    {
        #pragma acc loop gang(numGangs) vector_length(vectorLength)
        for (int x = 0; x < numGangs * vectorLength; ++x){
            /* Within a gang, or single, or parallel construct, a variable listed in the private 
            clause will be a different version for each worker or vector. */
            int private_variable = a[x];
            private_variable += 1;
            b[x] = private_variable;
        }
    }

    for (int x = 0; x < numGangs * vectorLength; ++x){
        if (b[x] != (a[x] + 1)){
            err = 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}