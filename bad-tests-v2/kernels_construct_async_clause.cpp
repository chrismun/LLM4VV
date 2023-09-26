#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:Kernels construct async clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int num_elements = 100;
    float *A = (float*) malloc(sizeof(float)*num_elements);
    float *B = (float*) malloc(sizeof(float)*num_elements);
    
    for(int i=0; i<num_elements; i++){
        A[i] = (float)rand()/(float)(RAND_MAX);
        B[i] = (float)rand()/(float)(RAND_MAX);
    }

    #pragma acc kernels async
    for(int i=0; i<num_elements; i++){
        B[i] = A[i] + B[i];
    }
    
    #pragma acc wait
    
    for(int i=0; i<num_elements; i++){
        if(A[i]+A[i] - B[i] > PRECISION){
            err = 1;
            break;
        }
    }
    free(A);
    free(B);

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