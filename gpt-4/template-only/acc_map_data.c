#include "acc_testsuite.h"
#include <stdlib.h>
#define SIZE 1024

//T1:acc map data,V:2.7-3.3
int test1() {
    int err = 0;
    float *hst = (float*)malloc(SIZE*sizeof(float));

    for (int i = 0; i < SIZE; ++i) {
        hst[i] = i+1;
    }

    #pragma acc enter data create(hst[0:SIZE])
    
    /*
    * Execute your parallel region here
    */
    
    #pragma acc exit data delete(hst[0:SIZE])
    
    for (int i = 0; i < SIZE; ++i) {
        if (abs(hst[i] - (i+1)) > 1e-5){
            err = 1;
            break;
        }
    }
    
    free(hst);
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
  
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
  
    return failcode;
}