#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:loop construct auto clause,V:2.0-2.7*/
int test1(){

    int err = 0;
    srand(SEED);
    int length = rand() % 10000 + 1; // random size of array

    int *a = (int*)malloc(length * sizeof(int));
    int *b = (int*)malloc(length * sizeof(int));

    for (int i = 0; i < length; ++i){
        int temp = rand();
        a[i] = temp;
        b[i] = temp;
    }

    /*
     * Compute using openACC loop auto 
     */
#pragma acc data copy(a[0:length])
    {
#pragma acc kernels
        {
#pragma acc loop auto
            for(int i = 0; i < length; i++){
                a[i]++;
            }
        }
    }
  
    /*
     * Compute using CPU
     */
    for(int i=0; i<length; i++){
        b[i]++;
    }

    /*
     * Verify correctness
     */
    for (int i = 0; i < length; ++i) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }
    
    free(a);
    free(b);
    
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