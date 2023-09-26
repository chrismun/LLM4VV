#include "acc_testsuite.h"

#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int* data_host;
    data_host = (int*)malloc(N*sizeof(int));

    int* data_device;
    data_device = (int*)acc_copyin(data_host, N*sizeof(int));

    #pragma acc data deviceptr(data_device)
    {
        #pragma acc parallel loop 
        for(int i = 0; i < N; i++){
            data_device[i] += 1;
        }
        #pragma acc exit data delete(data_device[0:N])
    }

    acc_copyout(data_host, N*sizeof(int));

    for(int i = 0; i < N; i++){
        if(data_host[i] != i + 1){
            err = 1;
        }
    }

    free(data_host);
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