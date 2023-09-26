#include "acc_testsuite.h"

#ifndef T1
int test1(){
    int err = 0;
    srand(SEED);
    int length = 16;
    int *A;
    int *B;
    int *C;
  
    A = (int*)malloc(length*sizeof(int));
    B = (int*)malloc(length*sizeof(int));
    C = (int*)malloc(length*sizeof(int));

    for(int i=0; i<length; i++){
        A[i] = rand()/(float)RAND_MAX;
        B[i] = rand()/(float)RAND_MAX;
    }
    
    #pragma acc parallel loop copyin(A[0:length], B[0:length]) copyout(C[0:length])
    for(int i=0; i<length; i++){
        C[i] = A[i] + B[i];
    }
    
    #pragma acc update host(C)
    
    for(int i=0; i<length; i++){
        if( A[i] + B[i] != C[i]){
            err = 1;
            break;
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