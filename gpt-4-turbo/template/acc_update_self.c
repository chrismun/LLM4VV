#include "acc_testsuite.h"
#ifndef T1
//T1:{data_construct, data_movement},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int a[size];
    int b[size];

    // Initialize host array
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = a[i]; // Copy to verify later
    }

    // Mark data for acceleration and modify on device
    #pragma acc data copy(a[0:size])
    {
      #pragma acc parallel loop
      for(int i = 0; i < size; ++i){
          a[i] += 5; // Any modification to test, simple add here
      }
      // Update the host (self) with the results
      #pragma acc update self(a[0:size])
    }

    // Verify the results
    for(int i = 0; i < size; ++i){
        if(a[i] != b[i] + 5){ // Check if the modification is reflected in the host data
            err++;
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