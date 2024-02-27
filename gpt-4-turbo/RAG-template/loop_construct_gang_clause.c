#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    const int gang_count = 256; // Assumed number of gangs for demonstration. Actual number depends on implementation and hardware.
    int *a = (int*)malloc(size * sizeof(int));
    
    // Initialize array
    for(int i = 0; i < size; ++i){
        a[i] = 0;
    }

    #pragma acc parallel num_gangs(gang_count)
    {
      #pragma acc loop gang
      for (int i = 0; i < size; ++i){
          // Increment the array value to indicate processing by a gang. In real parallel execution, multiple increments should occur simultaneously.
          a[i] += 1;
      }
    }

    for (int i = 0; i < size; ++i){
        if (a[i] != 1){
            err += 1; // If parallel execution is correct, each element should only be incremented once, indicating an error in execution if not.
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