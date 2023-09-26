#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct, collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int array[NUM_ELEMENTS][NUM_ELEMENTS];

    #pragma acc parallel loop collapse(2)
    for (int i=0; i<NUM_ELEMENTS; i++) {
        for (int j=0; j<NUM_ELEMENTS; j++) {
          array[i][j] = i + j;  
        }
    }

    for (int i=0; i<NUM_ELEMENTS; i++) {
        for (int j=0; j<NUM_ELEMENTS; j++) {
          if(array[i][j] != i + j) {
               err = 1;
          }
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