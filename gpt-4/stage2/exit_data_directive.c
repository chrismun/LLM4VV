#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>

#ifndef T1
/*T1:exit data directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand((unsigned int) time(NULL));

    // Create a test array
    int N = 750;  // To hold a sizable amount of data
    float *A = (float*) malloc(N*sizeof(float));

    // Initialize the values of A
    for(int i=0; i<N; i++){
      A[i] = (float)rand()/(float)RAND_MAX;
    }

    // Moving data to the device
    #pragma acc enter data create(A[0:N])

    // Operations and modifications on the device
    #pragma acc parallel loop present(A[0:N])
    for(int i=0; i<N; i++){
      A[i] += 5;
    }

    // Use exit data to remove from device.
    #pragma acc exit data delete(A[0:N])

    // Now test if A was freed properly
    if (acc_is_present(A, N*sizeof(float))){
        err = 1;
    }

    free(A);   // Freeing the memory allocated to A
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