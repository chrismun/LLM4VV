#include "acc_testsuite.h"
#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int* hostdata = (int *)malloc(n * sizeof(int));
    int * realdata = (int *)malloc(n * sizeof(int));
    
    for (int x = 0; x < n; ++x){
        hostdata[x] = 0;
        realdata[x] = 1;
    }
    #pragma acc data copy(hostdata[0:n])
    {
        acc_map_data(hostdata, realdata, n * sizeof(int));
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                hostdata[x] += realdata[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (hostdata[x] != 1){
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