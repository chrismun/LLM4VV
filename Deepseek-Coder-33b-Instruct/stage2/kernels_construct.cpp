#include <stdlib.h>
#include <iostream>
#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 100;
    int *data = new int[N];
    int *data_squared = new int[N];

    // Initialize data
    for(int i = 0; i < N; i++) {
        data[i] = rand() % 100;
        data_squared[i] = data[i] * data[i];
    }

    // Use OpenACC kernels construct to square each number
    #pragma acc kernels copy(data[0:N]) copyout(data_squared[0:N])
    {
        for(int i = 0; i < N; i++) {
            data_squared[i] = data[i] * data[i];
        }
    }

    // Check that the squares were correctly computed
    for(int i = 0; i < N; i++) {
        if(data_squared[i] != data[i] * data[i]) {
            err++;
        }
    }

    delete[] data;
    delete[] data_squared;

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