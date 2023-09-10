#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
#define T1
int test1(){
    int err = 0;
    srand(SEED);

    int size = 1024;
    int * h_array = (int*) malloc(size * sizeof(int));
    int * d_array;
    
    #pragma acc data create(d_array[0:size])
    {
        #pragma acc parallel loop
        for(int i = 0; i < size; i++) {
            d_array[i] = i;
        }

        #pragma acc update host(h_array[0:size])
        
        for(int i = 0; i < size; i++) {
            if (h_array[i] != i) {
                err = 1;
                break;
            }
        }
    }
    
    free(h_array);

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