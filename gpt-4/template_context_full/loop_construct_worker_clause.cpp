#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:loop construct worker clause,V:2.0-2.7*/
int test1(){
    int err=0;
    int num_gangs = 10;
    int num_workers = 4;
    srand(SEED);

    int* test_array = (int*)malloc(num_gangs*num_workers*sizeof(int));

    // incialize array
    for (int i = 0; i<num_gangs*num_workers; ++i){
        test_array[i] = 1;
    }

    // offload onto device and distribute loop across workers
    #pragma acc data copy(test_array[0:num_gangs*num_workers])
    {
        #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
        {
            #pragma acc loop gang 
            for(int i = 0; i < num_gangs; ++i)
            {
                #pragma acc loop worker
                for(int j = 0; j < num_workers; ++j)
                {
                    test_array[i*num_workers+j] += i+j;
                }
            }
        }
    }

    // Check all the sums are correct
    for(int i = 0; i < num_gangs; ++i)
    {
        for(int j = 0; j < num_workers; ++j)
        {
            if(test_array[i*num_workers+j] != 1+i+j)
            {
                err++;
            }
        }
    }

    free(test_array);
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