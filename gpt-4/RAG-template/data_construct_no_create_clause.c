#include "acc_testsuite.h"
#ifndef T1
#define T1

int test1(){
    int err = 0;
    srand(SEED);
    
    int* h_array;
    int length = 100;
    h_array = (int*)malloc(length*sizeof(int));

    #pragma acc data create(h_array[0:length])
    {
        
        for(int i=0; i<length; i++)
        {
            h_array[i] = i;
        }

        #pragma acc parallel loop present_or_no_create(h_array[0:length])
        for(int i=0; i<length; i++)
        {
            h_array[i] = h_array[i] * 2;
        }

        for(int i=0; i<length; i++)
        {
            if(h_array[i] != i*2)
            {
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