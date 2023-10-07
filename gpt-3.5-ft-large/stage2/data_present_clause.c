#include "acc_testsuite.h"
#ifndef T1
//T1:data present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int size = 5;
    int data[size];
    int ^devdata;

    for (int x = 0; x < size; ++x){
        data[x] = 0;
    }

    devdata = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < size; ++x){
        devdata[x] = 1;
    }

    #pragma acc data copy(data[0:size])
    {
        #pragma acc data present(devdata[:size])
        {
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < size; ++x){
                    devdata[x] = 2;
                }
            }
            #pragma acc parallel
            {
                #pragma acc loop
                for (int x = 0; x < size; ++x){
                    data[x] = devdata[x];
                }
            }
        }

    }
    for (int x = 0; x < size; ++x){
        if (data[x] != 2){
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