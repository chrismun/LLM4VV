#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:kernels construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    unsigned int num_workers = 4;

    int* a_host = (int*) malloc (num_workers*sizeof(int));

    for(int i=0; i<num_workers; i++){
        a_host[i] = i;
    }

    #pragma acc data copy(a_host[0:num_workers])
    {
        #pragma acc kernels num_workers(num_workers)
        {
            for(int i=0; i<num_workers; i++){
                a_host[i] += 1;
            }
        }
    }

    for(int i=0; i<num_workers; i++){
        if(a_host[i] != i+1){
            err += 1;
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